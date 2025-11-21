#include "QuadTreeNode.h"

#include "LeafActor.h"

void QuadTreeNode::Tick(UObject * Obj)
{
	DrawBound(Obj);
	if(!isLeaf)
	for(const auto & child : Child_Node){
		if(child.IsValid()){
			child->Tick(Obj);
		}
	}
}

QuadTreeNode::QuadTreeNode(const FVector& _center, const FVector& _extend ,TSharedPtr<QuadTreeNode>_root , int32 _Depth): center(_center),
                                                                                                           extend(_extend) , Root(_root) , Depth(_Depth)
{
	isLeaf = true;
	bInRange = false;
	Child_Node.Init(nullptr , 4);
}

QuadTreeNode::~QuadTreeNode()
{
	Objs.Empty();
	Child_Node.Empty();
}

bool QuadTreeNode::IsInBound(const FVector& InLoc) const
{
	return InLoc.X >=center.X - extend.X  &&
		InLoc.X <= center.X + extend.X &&
		InLoc.Y >=center.Y - extend.Y &&
		InLoc.Y <= center.Y + extend.Y ;
}

void QuadTreeNode::Subdivide()
{
	isLeaf = false;
	double x = center.X , y = center.Y , z = center.Z;
	double w = extend.X / 2, h = extend.Y /2 , l = extend.Z;
	Child_Node[0] = (MakeShared<QuadTreeNode>(FVector(x - w  ,y - h ,z) ,
		FVector(w,h,l) , AsShared(),Depth +1)  );

	Child_Node[1] = (MakeShared<QuadTreeNode>(FVector(x + w  ,y - h ,z) ,
		FVector(w,h,l),AsShared(),Depth +1) );

	Child_Node[2]=  (MakeShared<QuadTreeNode>(FVector(x - w  ,y + h ,z) ,
		FVector(w,h,l),AsShared(),Depth +1));

	Child_Node[3] = (MakeShared<QuadTreeNode>(FVector(x + w  ,y + h ,z) ,
		FVector(w,h,l) ,AsShared(),Depth +1));
	
	for(const auto & p : Objs)
	{
		if(!InsertToChild(p))
		{
			if(Root.IsValid())
			{
				Root->ReMatch(p);
			}
			else
			{
				Root->EscapeActors.Add(p);	
			}
		}
	}
	Objs.Empty();

}



bool QuadTreeNode::Insert(ALeafActor* Obj)
{
	if(!IsInBound(Obj->GetActorLocation()))
    {
     	return false;
    }
	if(isLeaf && Objs.Num() < maxCount)
	{
		Objs.Push(Obj);
		return  true;
	}
	if(isLeaf)
	{
		Subdivide();
	}
	return InsertToChild(Obj);
}

bool QuadTreeNode::InsertToChild(ALeafActor* Obj)
{
	for(const auto& child : Child_Node){
		if(child.IsValid() &&  child->Insert(Obj)){
			return true;
		}
	}
	return false;
}

bool QuadTreeNode::InterSectWithCircle(const FVector& Orign, float Radius) const 
{
	UE::Math::TBox<double> Box2(UE::Math::TVector(center.X- extend.X , center.Y - extend.Y , center.Z) , UE::Math::TVector(center.X+  extend.X , center.Y+ extend.Y , center.Z + 10.f));
	return 	FMath::SphereAABBIntersection(Orign , static_cast<double>(Radius) * static_cast<double>(Radius) , Box2);
}

bool QuadTreeNode::InterSectWithRecentage(const FVector& OtherCenter, const FVector& OtherExtent) const
{
	// 获取当前节点的中心、半尺寸和旋转
	FVector CenterA = this->center;
	FVector ExtentA = this->extend; 
    
	FVector CenterB = OtherCenter;
	FVector ExtentB = OtherExtent;
	// 计算中心距离（绝对值）
	float DeltaX = FMath::Abs(CenterA.X - CenterB.X);
	float DeltaY = FMath::Abs(CenterA.Y - CenterB.Y);
    
	// 计算半尺寸和
	float SumExtentX = ExtentA.X + ExtentB.X;
	float SumExtentY = ExtentA.Y + ExtentB.Y;
    
	// 分离轴检测
	bool bOverlapX = DeltaX <= SumExtentX;
	bool bOverlapY = DeltaY <= SumExtentY;
    
	return bOverlapX && bOverlapY;
}

void QuadTreeNode::CheckIn(const FVector& _center, float Radious, bool IsParent)
{
	bInRange = IsParent &&  InterSectWithCircle(_center ,Radious );
	if(!isLeaf){
		for(const auto & Child : Child_Node){
			Child->CheckIn(_center , Radious,bInRange);
		}
	}
	else{
		for(const auto & obj : Objs){
			obj->Active(obj->HasCollision(_center , Radious));	
		}
	}
}


bool QuadTreeNode::InterSection(const FVector& _pMin, const FVector& _pMax, const FVector& _point)
{		
	return (_point.X >= _pMin.X &&
		_point.X <= _pMax.X &&
		_point.Y >= _pMin.Y &&
		_point.Y <= _pMax.Y);
}

void QuadTreeNode::DrawBound(const UObject * Obj) const
{
		FColor drawColor = bInRange ? FColor::Green : FColor::Red;
		FVector drawCenter = center + (bInRange ? FVector(0, 0, 8) : FVector(0, 0, 5));
		DrawDebugBox(Obj ->GetWorld(), drawCenter , extend + FVector(0,0,1) ,drawColor , false,-1.f , 0,10.f);
}

bool QuadTreeNode::ReMatch(ALeafActor* Actor)
{
	if(Actor && Insert(Actor))
	{
		return true;
	}
	if(Root.IsValid() && Root->ReMatch(Actor))
	{
		return true;
	}
	EscapeActors.Add(Actor);
	UE_LOG(LogTemp , Warning , TEXT("Hi This is A Leaf Escape"));
	return false;
}
void QuadTreeNode::update()
{
	if(!isLeaf)
	{
		for(const auto & child : Child_Node){
			child->update();
		}
	}
	else{
		TArray<ALeafActor *> DeleteArray;
		for(ALeafActor * obj : Objs)
		{
			if(!IsInBound(obj->GetActorLocation())){
				if(Root.IsValid()){
					Root->ReMatch(obj);
				}
				else{
					EscapeActors.Add(obj);
				}
				DeleteArray.Add(obj);
			}
		}
		for(const auto & del : DeleteArray)
		{
			Objs.RemoveSingle(del);
		}
	}
}


