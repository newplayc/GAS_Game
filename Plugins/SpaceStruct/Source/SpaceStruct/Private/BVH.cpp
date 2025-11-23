#include "BVH.h"

#include "BaseGizmos/GizmoElementShared.h"


BVH::BVH() : RootHandle(INDEX_NONE) , SplitStrategy(EBVHSplitStrategy::SAH) , MaxPrimitivesPerLeaf(4), RebalanceThreshold(0.7f), LooseFactor(1.2f),
             PrimitiveCount(0) , FrameCounter(0),TimeSinceLastRebalance(0.0f)

{
	Nodes.Reserve(1024);
}

BVH::~BVH()
{
	if (RootHandle .IsValid())
	{
		FreeSubtree(RootHandle);
	}
}
// =====基本操作====
FBVHNodeHandle BVH::InsertPrimitive(int32 PrimitiveID, const FBox& WorldBounds)
{
	if (!WorldBounds.IsValid())
	{
		return FBVHNodeHandle();
	}
	// 分配新节点
	FBVHNodeHandle NewNodeHandle = AllocateNode();
	FBVHNode& NewNode = Nodes[NewNodeHandle.Index];

	//初始化节点
	NewNode.Bounds = WorldBounds;
	NewNode.PrimitiveIDs.Add(PrimitiveID);
	NewNode.LastUpdateTime = 0.0f;

	// 如果第一个图元 设置根节点
	if (!RootHandle.IsValid())
	{
		RootHandle = NewNodeHandle;
		return NewNodeHandle;
	}

	// 不是第一个 证明 需要从根节点 自顶向下 找到最佳插入位置
	FBVHNodeHandle CurrentNodeHandle = RootHandle;
	while (true)
	{
		FBVHNode& CurrentNode = Nodes[CurrentNodeHandle.Index];
		if (CurrentNode.IsLeaf())
		{
			// 步骤5: 如果是叶子节点，检查是否需要分裂
			// 不用分裂 
			if (CurrentNode.PrimitiveIDs.Num() < MaxPrimitivesPerLeaf)
			{
				CurrentNode.PrimitiveIDs.Add(PrimitiveID);
				CurrentNode.Bounds = CurrentNode.Bounds + WorldBounds;
				CurrentNode.MarkDirty();
				DirtyNodes.Add(CurrentNodeHandle);

				// 释放分配的节点(因为合并到 现有节点了  意味着有人 传进来的信息了)
				FreeNode(NewNodeHandle);
				return CurrentNodeHandle;
			}
			else
			{
				// 分裂节点
				TArray<FBVHNodeHandle>AllPrimitives;
				// 添加现有图元
				for (int32 ExistingID : CurrentNode.PrimitiveIDs)
				{
					// 为每个现有图元创建临时节点句柄
					// 注意：这里简化处理，实际应该存储图元到节点的映射
					FBVHNodeHandle TempHandle = AllocateNode();
					Nodes[TempHandle.Index].PrimitiveIDs.Add(ExistingID);
					Nodes[TempHandle.Index].Bounds = CurrentNode.Bounds; // 简化
					AllPrimitives.Add(TempHandle);
				}
				// 加入 新的图元
				AllPrimitives.Add(NewNodeHandle);
				// 清空 当前节点
				CurrentNode.PrimitiveIDs.Empty();

				SplitNode(CurrentNodeHandle , MoveTemp(AllPrimitives));
				return NewNodeHandle;
			}
		}

	}
	
}


// ==================== 节点管理 ====================
FBVHNodeHandle BVH::AllocateNode()
{
	int32 Index = Nodes.AddDefaulted();
	return FBVHNodeHandle(Index);
}

void BVH::FreeNode(FBVHNodeHandle Handle)
{
	if (Handle.IsValid())
	{
		//标记无效
		Nodes[Handle.Index] = FBVHNode();
	}
}

void BVH::FreeSubtree(FBVHNodeHandle RootHandle)
{
	if (!RootHandle.IsValid())return;
	TArray<FBVHNodeHandle>NodesToFree;
	NodesToFree.Add(RootHandle);
	    
	for (int32 i = 0; i < NodesToFree.Num(); ++i)
	{
		FBVHNode& Node = Nodes[NodesToFree[i].Index];
        
		if (Node.LeftChild.IsValid())
			NodesToFree.Add(Node.LeftChild);
		if (Node.RightChild.IsValid())
			NodesToFree.Add(Node.RightChild);
        
		FreeNode(NodesToFree[i]);
	}
}


FBVHNodeHandle BVH::BuildSubtree(TArray<FBVHNodeHandle>&& PrimitiveHandles)
{
	if (PrimitiveHandles.Num() == 0)
	{
		return FBVHNodeHandle();
	}
	// 如果 图元 小于 叶子 叶子节点 创建叶子节点
	if (PrimitiveHandles.Num() <= MaxPrimitivesPerLeaf)
	{
		FBVHNodeHandle LeafHandle = AllocateNode();
		FBVHNode& LeafNode = Nodes[LeafHandle.Index];
        
		// 合并所有图元到叶子节点
		FBox MergedBounds(ForceInit);
		for (const FBVHNodeHandle& Handle : PrimitiveHandles)
		{
			LeafNode.PrimitiveIDs.Append(Nodes[Handle.Index].PrimitiveIDs);
			MergedBounds += Nodes[Handle.Index].Bounds;
			FreeNode(Handle); // 释放临时节点
		}
		LeafNode.Bounds = MergedBounds;
		return LeafHandle;
	}
	// 步骤2: 创建内部节点并分割
	FBVHNodeHandle InternalHandle = AllocateNode();
	SplitNode(InternalHandle, MoveTemp(PrimitiveHandles));
	return InternalHandle;
}

//============ 构建系统==================
void BVH::SplitNode(FBVHNodeHandle NodeHandle, TArray<FBVHNodeHandle>&& PrimitiveHandles)
{
	FBVHNode& Node = Nodes[NodeHandle.Index];
	if (PrimitiveHandles.Num() <= 1)
	{
		//无法分割 退回
		for (FBVHNodeHandle Handle : PrimitiveHandles)
		{
			Node.PrimitiveIDs.Append(Nodes[Handle.Index].PrimitiveIDs);
			FreeNode(Handle);
		}
		return;
	}

	// 步骤1 根据策略 选择 分割方法
	TArray<FBVHNodeHandle> LeftPrimitives, RightPrimitives;
	int32 SplitAxis = 0;
	float SplitPosition = 0.0f;
	bool bSplitSuccess = false;
	switch (SplitStrategy)
	{
	case EBVHSplitStrategy::SAH:
		{
			bSplitSuccess = TrySplitWithSAH(PrimitiveHandles , SplitAxis , SplitPosition, LeftPrimitives, RightPrimitives);
			if (!bSplitSuccess)
			{
				// SAH失败,回退到等量分割
				FBox TotalBounds = CalculateMergedBounds(PrimitiveHandles);
				FVector Extent = TotalBounds.GetSize();
			
				SplitAxis = (Extent.X > Extent.Y && Extent.X > Extent.Z) ? 0 : 
				  (Extent.Y > Extent.Z) ? 1 : 2;

				SplitEqualCounts(PrimitiveHandles , SplitAxis, LeftPrimitives, RightPrimitives);
				bSplitSuccess = true;
			}
		}
		break;
	case EBVHSplitStrategy::EqualCounts:
		{
			FBox TotalBounds = CalculateMergedBounds(PrimitiveHandles);
			FVector Extent = TotalBounds.GetSize();
			
			SplitAxis = (Extent.X > Extent.Y && Extent.X > Extent.Z) ? 0 : 
			  (Extent.Y > Extent.Z) ? 1 : 2;

			SplitEqualCounts(PrimitiveHandles , SplitAxis, LeftPrimitives, RightPrimitives);
			bSplitSuccess = true;
		}
		break;
	case EBVHSplitStrategy::Middle :
		{
			FBox TotalBounds = CalculateMergedBounds(PrimitiveHandles);
			FVector Center = TotalBounds.GetCenter();
			FVector Extent = TotalBounds.GetSize();
			SplitAxis = (Extent.X > Extent.Y && Extent.X > Extent.Z) ? 0 : 
		   (Extent.Y > Extent.Z) ? 1 : 2;
		
			float SplitValue = Center[SplitAxis];
			for (const FBVHNodeHandle& Handle : PrimitiveHandles)
			{
				const FBVHNode& PrimNode = Nodes[Handle.Index];
				FVector PrimCenter = PrimNode.Bounds.GetCenter();
	                
				if (PrimCenter[SplitAxis] < SplitValue)
					LeftPrimitives.Add(Handle);
				else
					RightPrimitives.Add(Handle);
			}
			if (LeftPrimitives.Num() == 0 || RightPrimitives.Num() == 0)
			{
				// 中点分割失败 回退到等量分割
				SplitEqualCounts(PrimitiveHandles , SplitAxis, LeftPrimitives, RightPrimitives);
			}
			bSplitSuccess = true;
		}
		break;
	default:
		SplitEqualCounts(PrimitiveHandles , 0, LeftPrimitives, RightPrimitives);
		bSplitSuccess = true;
		break;
	}
	if (!bSplitSuccess|| LeftPrimitives.Num() == 0 ||  RightPrimitives.Num() ==0)
	{
		// 都失败 创建叶子节点
		for (FBVHNodeHandle Handle : PrimitiveHandles)
		{
			Node.PrimitiveIDs.Append(Nodes[Handle.Index].PrimitiveIDs);
			FreeNode(Handle);
		}
		return;
	}
	
	//创建子节点
	if (LeftPrimitives.Num() == 1)
	{
		// 只有一个图元，直接使用现有节点
		Node.LeftChild = LeftPrimitives[0];
		Nodes[LeftPrimitives[0].Index].Parent = NodeHandle;
	}
	else
	{
		// 多个图元，递归构建子树
		Node.LeftChild = BuildSubtree(MoveTemp(LeftPrimitives));
		if (Node.LeftChild.IsValid())
		{
			Nodes[Node.LeftChild.Index].Parent = NodeHandle;
		}
	}
	if (RightPrimitives.Num() == 1)
	{
		// 只有一个图元，直接使用现有节点
		Node.RightChild = RightPrimitives[0];
		Nodes[RightPrimitives[0].Index].Parent = NodeHandle;
	}
	else
	{
		// 多个图元，递归构建子树
		Node.RightChild = BuildSubtree(MoveTemp(RightPrimitives));
		if (Node.RightChild.IsValid())
		{
			Nodes[Node.RightChild.Index].Parent = NodeHandle;
		}
	}

	// 步骤6: 更新当前节点的包围盒
	FBox NewBounds(ForceInit);
	if (Node.LeftChild.IsValid())
	{
		NewBounds += Nodes[Node.LeftChild.Index].Bounds;
	}
	if (Node.RightChild.IsValid())
	{
		NewBounds += Nodes[Node.RightChild.Index].Bounds;
	}
	Node.Bounds = NewBounds;

	// 步骤7: 标记节点需要更新父节点
	Node.MarkDirty();
	DirtyNodes.Add(NodeHandle);
}

bool BVH::TrySplitWithSAH(const TArray<FBVHNodeHandle>& PrimitiveHandles, int32& OutSplitAxis, float& OutSplitPosition,
	TArray<FBVHNodeHandle>& OutLeft, TArray<FBVHNodeHandle>& OutRight)
{
	if (PrimitiveHandles.Num() <= 2)
		return false;
	FBox TotalBounds = CalculateMergedBounds(PrimitiveHandles);
	//FVector Center = CalculateBoundsCenter(PrimitiveHandles);
	float BestCost = FLT_MAX;
	int32 BestAxis = -1;
	float BestSplit = 0.0f;

	// 在三个轴上测试分割
	for (int32 Axis = 0; Axis < 3; ++Axis)
	{
		TArray<FBVHNodeHandle> SortedPrimitives = PrimitiveHandles;
		SortedPrimitives.Sort([this, Axis](const FBVHNodeHandle& A, const FBVHNodeHandle& B) {
		FVector CenterA = Nodes[A.Index].Bounds.GetCenter();
		FVector CenterB = Nodes[B.Index].Bounds.GetCenter();
		return CenterA[Axis] < CenterB[Axis];
		});

		//使用 桶方法 计算 SAH成本
		constexpr int32 NumBuckets = 12;
		TArray<FBox> LeftBounds, RightBounds;
		TArray<int32> LeftCounts, RightCounts;
		
		LeftBounds.SetNumZeroed(NumBuckets);
		LeftCounts.SetNumZeroed(NumBuckets);
		RightBounds.SetNumZeroed(NumBuckets);
		RightCounts.SetNumZeroed(NumBuckets);

		float AxisMin = TotalBounds.Min[Axis];
		float AxisMax = TotalBounds.Max[Axis];
		float BucketWidth = (AxisMax - AxisMin) / NumBuckets;

		for (const FBVHNodeHandle & Handle : SortedPrimitives)
		{
			const FBVHNode& Node = Nodes[Handle.Index];
			FVector PrimCenter = Node.Bounds.GetCenter();

			
			int32 BucketIndex = FMath::Clamp(
	FMath::FloorToInt((PrimCenter[Axis] - AxisMin) / BucketWidth),
	0, NumBuckets - 1);

			// 更新左边界
			for (int32 i = BucketIndex; i < NumBuckets; ++i)
			{
				LeftBounds[i] += Node.Bounds;
				LeftCounts[i]++;
			}
			for (int32 i = 0; i < NumBuckets; ++i)
			{
				RightBounds[i] += Node.Bounds;
				RightCounts[i]++;
			}
		}
		// 找到 最优分割点
		for (int32 SplitIndex = 1; SplitIndex < NumBuckets; ++SplitIndex)
		{
			if (LeftCounts[SplitIndex-1] ==0 || RightCounts[SplitIndex] ==0)
				continue;
			float Cost = CalculateSAHCost(LeftCounts[SplitIndex-1], LeftBounds[SplitIndex-1]
				, RightCounts[SplitIndex], RightBounds[SplitIndex]);

			if (Cost < BestCost)
			{
				BestCost = Cost;
				BestAxis = Axis;
				BestSplit = AxisMin + SplitIndex * BucketWidth;
			}
		}
	}
	if (BestAxis == -1)return false;
	// 应用最优 分割
	OutSplitAxis = BestAxis;
	OutSplitPosition = BestSplit;
	for (const FBVHNodeHandle& Handle : PrimitiveHandles)
	{
		const FBVHNode& Node = Nodes[Handle.Index];
		FVector NodeCenter = Node.Bounds.GetCenter();
		if (NodeCenter[BestAxis] < BestSplit)
			OutLeft.Add(Handle);
		else
			OutRight.Add(Handle);
	}
	return !OutLeft.IsEmpty() && !OutRight.IsEmpty();
}

void BVH::SplitEqualCounts(const TArray<FBVHNodeHandle>& PrimitiveHandles, int32 SplitAxis,
	TArray<FBVHNodeHandle>& OutLeft, TArray<FBVHNodeHandle>& OutRight)
{
	TArray<FBVHNodeHandle> SortedPrimitives = PrimitiveHandles;
	SortedPrimitives.Sort([this, SplitAxis](const FBVHNodeHandle& A, const FBVHNodeHandle& B) {
	FVector CenterA = Nodes[A.Index].Bounds.GetCenter();
	FVector CenterB = Nodes[B.Index].Bounds.GetCenter();
	return CenterA[SplitAxis] < CenterB[SplitAxis];
	});

	int32 SplitIndex = SortedPrimitives.Num() / 2;
	OutLeft.Append(SortedPrimitives.GetData() , SplitIndex);
	OutRight.Append(SortedPrimitives.GetData() + SplitIndex , SortedPrimitives.Num() - SplitIndex);
}
// ========动态更新 =====
// 自底向上 更新节点包围盒
void BVH::RefitNode(FBVHNodeHandle NodeHandle)
{
	FBVHNode & Node  = Nodes[NodeHandle.Index];
	if (Node.IsLeaf())
	{
		FBox NewBounds(ForceInit);
		for (int32 PrimitiveID : Node.PrimitiveIDs)
		{
			// 叶子节点：重新计算所有图元的合并包围盒
			//TODO
			// 这里应该从外部系统获取图元的最新包围盒
			// FBox PrimBounds = GetPrimitiveBounds(PrimitiveID);
			// NewBounds += PrimBounds;

			NewBounds +=  Node.Bounds;
		}
		Node.Bounds = NewBounds;
	}
	else
	{
		// 内部节点 ; 合并子节点的包围盒
		FBox NewBounds(ForceInit);
		if (Node.LeftChild.IsValid())
		{
			NewBounds += Nodes[Node.LeftChild.Index].Bounds;
		}
		if (Node.RightChild.IsValid())
		{
			NewBounds += Nodes[Node.RightChild.Index].Bounds;
		}
		Node.Bounds = NewBounds;
	}
	Node.ClearDirty();
	// 父节点 需要更新
	if (Node.Parent.IsValid())
	{
		Nodes[Node.Parent.Index].MarkDirty();
		DirtyNodes.Add(Node.Parent);
	}
}

void BVH::CheckAndRebalanceSubtree(FBVHNodeHandle NodeHandle)
{
	if (!NodeHandle.IsValid())return;
	FBVHNode& Node = Nodes[NodeHandle.Index];
	float BalanceFactor = CalculateNodeBalanceFactor(NodeHandle);
	if (BalanceFactor > RebalanceThreshold)
	{
		RebuildSubtree(NodeHandle);
	}
}

void BVH::RebuildSubtree(FBVHNodeHandle NodeHandle)
{
	
}

float BVH::CalculateNodeBalanceFactor(FBVHNodeHandle NodeHandle) const
{
	
}


//===============辅助函数=================

FVector BVH::CalculateBoundsCenter(const TArray<FBVHNodeHandle>& PrimitiveHandles) const
{
	FVector Sum(0,0,0);
	for (const FBVHNodeHandle& Handle : PrimitiveHandles)
	{
		Sum += Nodes[Handle.Index].Bounds.GetCenter();
	}
	return Sum / FMath::Max(1, PrimitiveHandles.Num());
}

// 
FBox BVH::CalculateMergedBounds(const TArray<FBVHNodeHandle>& PrimitiveHandles) const
{
	FBox MergedBounds(ForceInit);
	for (const FBVHNodeHandle& Handle : PrimitiveHandles)
	{
		MergedBounds += Nodes[Handle.Index].Bounds;
	}
	return MergedBounds;
}

float BVH::CalculateSAHCost(int32 LeftCount, const FBox& LeftBounds, int32 RightCount, const FBox& RightBounds) const
{
	constexpr float TraversalCost = 1.0f;
	constexpr float IntersectionCost = 1.0f;
	float LeftArea = GetSurfaceArea<float>(LeftBounds);
	float RightArea = GetSurfaceArea<float>(RightBounds);

	return TraversalCost + 
	   (LeftCount * IntersectionCost * LeftArea + 
		RightCount * IntersectionCost * RightArea);
}
