// Fill out your copyright notice in the Description page of Project Settings.



#include "PMazeCreator.h"

#include "LevelViewportClickHandlers.h"
#include "VectorUtil.h"
#include "BaseGizmos/GizmoElementArrow.h"
#include "Util/ColorConstants.h"

// Sets default values
AMazeCreator::AMazeCreator()
{
	PrimaryActorTick.bCanEverTick = false;
	DefaultRoot = CreateDefaultSubobject<USceneComponent>("DefaultComponent");
	RootComponent = DefaultRoot;	
}

void AMazeCreator::BeginPlay()
{
	Super::BeginPlay();
	if(Height >=3 && Width >= 3)
	{
		SpawnMaze();
	}
}
// 随机获取 边界的一个点并且 都是 奇数的 点
TTuple<int32, int32,int32>AMazeCreator::GetBorderRandomLoc(int32 Width, int32 Height)
{
	int32 RandDir = FMath::RandRange(1 , 4);
	TTuple<int32 , int32,int32>Res;
	Res.Get<2>()  = RandDir;
	switch (RandDir)
	{
	case 1:
		Res.Get<0>() = 1;
		Res.Get<1>() = FMath::RandRange(1 ,Width - 1);
		break;
	case 2:
		Res.Get<0>() = FMath::RandRange(1 , Height-1);
		Res.Get<1>() = Width - 1;
		break;
	case 3:
		Res.Get<0>() = Height - 1;
		Res.Get<1>() =FMath::RandRange(1 ,Width - 1);
		break;
	case 4:
		Res.Get<0>() = FMath::RandRange(1 , Height-1);
		Res.Get<1>() = 1;
		break;
	default:
		break;
	}
	if( (Res.Get<0>() & 1) == 0)
	{
		Res.Get<0>() -= 1;
	}
	if((Res.Get<1>() & 1) ==0)
	{
		Res.Get<1>() -= 1;
	}
	return Res;
}

void AMazeCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMazeCreator::SpawnMaze()
{
	switch (creationMode)
	{
	case 0:
		DfsSpawn();
	break;
	case 1:
		PrimSpawn();
		break;
	case 2:
		CubeSplit();
		break;
	default: ;
	}
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle ,this ,  &ThisClass::ChangeMesh, playRate,true);
}

void AMazeCreator::DfsSpawn()
{
	// 1 是路  0 墙 初始化  -1 访问过 别访问了
	roadArr  = std::vector(Height , std::vector(Width , 0));
	// 初始化 网格 
	for(int32 i = 0; i < Height; i++){
		for(int32 j = 0; j < Width;j++){
			UStaticMeshComponent * NewCube =  NewObject<UStaticMeshComponent>(this);
			NewCube->SetupAttachment(RootComponent);
			NewCube->RegisterComponent();
			// 边界
			if(i == 0 || i == Height - 1 || j == 0 || j == Width-1)
			{
				NewCube->SetStaticMesh(BlockMesh);
				NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , MeshWidth /2));	
			}
			else if(i & 1  && j & 1)
			{
				NewCube->SetStaticMesh(PlaneMesh);
				NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , 0));
				roadArr[i][j] = 1;
			}
			else
			{
				NewCube->SetStaticMesh(BlockMesh);
				NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , MeshWidth /2));	
			}
			SpawnStaticMeshes.Add(NewCube);
		}
	}
	
	TArray<TTuple<int32 , int32 , TArray<Point>>>Stack;
    TTuple<int32 , int32 , int32> Begin =  GetBorderRandomLoc(Width-1, Height-1);
	
	TArray<Point>DirArray = {Point{0,-2} , Point{0,2} , Point{2,0},Point{-2,0}};
	
	Stack.Push(TTuple<int32 , int32 , TArray<Point>>(Begin.Get<0>() , Begin.Get<1>(),DirArray));
	roadArr[Begin.Get<0>()][Begin.Get<1>()] = -1;
	
	while(Stack.Num() > 0)
	{
		auto [x , y , Dir] = Stack.Top();
		Stack.Pop();
		while(Dir.Num() > 0)
		{
			int32 RandDir = FMath::RandRange(0 , Dir.Num()-1);
			const int newx = x + Dir[RandDir].x;
			const int newy = y + Dir[RandDir].y;
			if(newx < Height  && newx >= 0 && newy < Width  && newy >= 0 && roadArr[newx][newy] == 1)
			{
				int Roadx = x + Dir[RandDir].x / 2;
				int Roady = y + Dir[RandDir].y /2;
				if(roadArr[Roadx][Roady] == 0)
				{
					roadArr[Roadx][Roady] = -1;
					roadArr[newx][newy] = -1;
					taskQueue.Enqueue({Roadx , Roady});
					Dir.RemoveAt(RandDir);
					if(Dir.Num() > 0)
					{
						Stack.Push({x, y , Dir});
					}
					Stack.Push({newx , newy ,DirArray});
					break;
				}
			}
			Dir.RemoveAt(RandDir);
		}
	}
}
// 生成 概率公式RoomNum * (1 - (RoomSize * (1- 当前的1为左上角 面积的 最大占比 /  ？)))
// 过大的 RoomSize 或造成 没有方块 ， 概率公式 可以自行更改
/*
 * 问题 : 是否要考虑剩余面积 对 生成概率的影响 
 */
void AMazeCreator::CubeSplit()
{

	// 1 是路  0 墙 初始化  -1 访问过 别访问了
	CubeFlag =  std::vector(Height , std::vector(Width , false));
	roadArr  = std::vector(Height , std::vector(Width , 0));

	// 初始化
	for(int32 i = 0; i < Height; i++){
		for(int32 j = 0; j < Width;j++){
			UStaticMeshComponent * NewCube =  NewObject<UStaticMeshComponent>(this);
			NewCube->SetupAttachment(RootComponent);
			NewCube->RegisterComponent();
			// 边界
			if(i == 0 || i == Height - 1 || j == 0 || j == Width-1)
			{
				NewCube->SetStaticMesh(BlockMesh);
				NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , MeshWidth /2));	
			}
			else if(i & 1  && j & 1)
			{
				if(CubeFlag[i][j] == false&&CubeFlag[i-1][j] == false  && CubeFlag[i][j-1]== false && CubeFlag[i][j+1]== false)
				{
					// 公式
					float Area = static_cast<float>(Height - i)  * (Width - j) / static_cast<float>(Width * Height);
					float probability = RoomNum * (1 - RoomSize + RoomSize * Area / 5.f) * 100.f;
					UE_LOG(LogTemp , Warning , TEXT("Probability %f") , probability);
					if(FMath::RandRange(0.f , 100.f) < probability)
					{
						int32 CWidth = (Width - j-1) * FMath::RandRange(0.f , RoomSize);
						if((CWidth & 1) == 1) {CWidth+=1;}
						int32 CHeight =(Height - i-1) *  FMath::RandRange(0.f , RoomSize);
						if((CHeight & 1)==1){CHeight+=1;}
						for(; CHeight >=0; CHeight--)
						{
							for(int t = CWidth;t >=0; t--)
							{
								CubeFlag[i + CHeight][j + t] = true;
							}
						}
					}
				}
				NewCube->SetStaticMesh(PlaneMesh);
				NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , 0));
				roadArr[i][j] = 1;
			}
			else
			{
				if(CubeFlag[i][j]){
					NewCube->SetStaticMesh(PlaneMesh);
					NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , 0));
				}
				else{
					NewCube->SetStaticMesh(BlockMesh);
					NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , MeshWidth /2));	
				}	
			}
			SpawnStaticMeshes.Add(NewCube);
		}
	}
	
}

void AMazeCreator::PrimSpawn()
{

	// 0 是灰色0 (代表墙壁)
	// 2 蓝色0  代表待检测点
	// 1 是 黄色1
	// -1 红色的 1 (已经是 陆地了)
	// 3 报废 0
	// 初始化
	roadArr  = std::vector(Height , std::vector(Width , 0));
	
	for(int32 i = 0; i < Height; i++){
		for(int32 j = 0; j < Width;j++){
			UStaticMeshComponent * NewCube =  NewObject<UStaticMeshComponent>(this);
			NewCube->SetupAttachment(RootComponent);
			NewCube->RegisterComponent();
			// 边界
			if(i == 0 || i == Height - 1 || j == 0 || j == Width-1)
			{
				NewCube->SetStaticMesh(BlockMesh);
				NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , MeshWidth /2));	
			}
			else if(i & 1  && j & 1)
			{
				NewCube->SetStaticMesh(PlaneMesh);
				NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , 0));
				roadArr[i][j] = 1;
			}
			else
			{
				NewCube->SetStaticMesh(BlockMesh);
				NewCube->SetRelativeLocation(FVector(j* MeshWidth , i * MeshWidth , MeshWidth /2));	
			}
			SpawnStaticMeshes.Add(NewCube);
		}
	}

	
	TArray<Point>DirArray1 = {Point{0,-1} , Point{0,1} , Point{1,0},Point{-1,0}};
	TArray<Point>DirArray2 = {Point{0,-2} , Point{0,2} , Point{2,0},Point{-2,0}};
	
	TArray<TTuple<int32 , int32 , int32,int32>>YellowAndBlue;
	TTuple<int32 , int32 , int32> Begin =  GetBorderRandomLoc(Width-1, Height-1);
	int bex = Begin.Get<0>() ,bey = Begin.Get<1>();
	roadArr[bex][bey] = -1;

	
	for(int i =0; i < 4; i ++)
	{
		int newx = bex + DirArray2[i].x , newy = bey + DirArray2[i].y;
		if(newx >= 0 && newx < Height && newy >= 0 && newy < Width)
		{
			YellowAndBlue.Add({newx , newy , bex + DirArray1[i].x , bey + DirArray1[i].y});
			roadArr[bex + DirArray1[i].x][bey+ DirArray1[i].y] = 2;
		}
	}
	while(YellowAndBlue.Num()> 0)
	{
		float Rd = FMath::RandRange(0 , YellowAndBlue.Num() - 1);
		auto[yx , yy , bx , by] =  YellowAndBlue[Rd];
		if(roadArr[yx][yy] == 1)
		{
			roadArr[bx][by] = -1;
			roadArr[yx][yy] = -1;
			taskQueue.Enqueue({bx , by});
			
			for(int i =0; i < 4; i ++)
			{
				int newx = yx + DirArray2[i].x ,newy = yy + DirArray2[i].y;
				if(newx >= 0 && newx < Height && newy >= 0 && newy < Width && roadArr[newx][newy] ==1)
				{
					if(roadArr[yx + DirArray1[i].x][yy+ DirArray1[i].y] == 0)
					{
						YellowAndBlue.Add({newx , newy , yx + DirArray1[i].x , yy + DirArray1[i].y});
						roadArr[yx + DirArray1[i].x][yy+ DirArray1[i].y] = 2;	
					}
				}
			}
		}
		else
		{
			roadArr[bx][by] = 3;
		}
		YellowAndBlue.RemoveAt(Rd);
	}
}

void AMazeCreator::ChangeMesh()
{
	if(!taskQueue.IsEmpty())
	{
		auto[x, y] = *taskQueue.Peek();
		UE_LOG(LogTemp , Warning , TEXT("%d , %d Mesh") , x , y);
		
		SpawnStaticMeshes[x * Width + y]->SetStaticMesh(PlaneMesh);
		SpawnStaticMeshes[x * Width + y]->AddRelativeLocation(FVector(0,0,-MeshWidth/2));
		taskQueue.Pop();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

