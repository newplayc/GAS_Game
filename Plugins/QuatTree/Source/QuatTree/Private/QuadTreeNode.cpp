#include "QuadTreeNode.h"
#include "LeafActor.h"
#include "DrawDebugHelpers.h"

QuadTreeNode::QuadTreeNode(const FVector& InCenter, const FVector& InExtent, TSharedPtr<QuadTreeNode> InParent, int32 InDepth)
	: Center(InCenter)
	, Extent(InExtent)
	, Parent(InParent)
	, bIsLeaf(true)
	, bInRange(false)
	, Depth(InDepth)
{
	Objects.Reserve(MaxObjectsPerNode);
	for (int32 i = 0; i < 4; ++i)
	{
		Children[i] = nullptr;
	}
}

QuadTreeNode::~QuadTreeNode()
{
	Objects.Empty();
	for (int32 i = 0; i < 4; ++i)
	{
		Children[i].Reset();
	}
}

bool QuadTreeNode::IsInBounds(const FVector& Location) const
{
	return FMath::Abs(Location.X - Center.X) <= Extent.X &&
	       FMath::Abs(Location.Y - Center.Y) <= Extent.Y;
}

void QuadTreeNode::Subdivide()
{
	if (Depth >= MaxDepth)
	{
		return;
	}

	bIsLeaf = false;
	
	const double HalfX = Extent.X * 0.5;
	const double HalfY = Extent.Y * 0.5;
	const double Z = Center.Z;
	const FVector ChildExtent(HalfX, HalfY, Extent.Z);
	
	// 创建四个子节点: 左下, 右下, 左上, 右上
	Children[0] = MakeShared<QuadTreeNode>(FVector(Center.X - HalfX, Center.Y - HalfY, Z), ChildExtent, AsShared(), Depth + 1);
	Children[1] = MakeShared<QuadTreeNode>(FVector(Center.X + HalfX, Center.Y - HalfY, Z), ChildExtent, AsShared(), Depth + 1);
	Children[2] = MakeShared<QuadTreeNode>(FVector(Center.X - HalfX, Center.Y + HalfY, Z), ChildExtent, AsShared(), Depth + 1);
	Children[3] = MakeShared<QuadTreeNode>(FVector(Center.X + HalfX, Center.Y + HalfY, Z), ChildExtent, AsShared(), Depth + 1);
	
	// 重新分配现有对象到子节点
	for (ALeafActor* Actor : Objects)
	{
		if (!InsertToChild(Actor))
		{
			if (Parent.IsValid())
			{
				Parent->ReInsert(Actor);
			}
			else
			{
				EscapeActors.Add(Actor);
			}
		}
	}
	
	Objects.Empty();
}



bool QuadTreeNode::Insert(ALeafActor* Actor)
{
	if (!Actor || !IsInBounds(Actor->GetActorLocation()))
	{
		return false;
	}

	if (bIsLeaf)
	{
		if (Objects.Num() < MaxObjectsPerNode)
		{
			Objects.Add(Actor);
			return true;
		}
		
		Subdivide();
	}
	
	return InsertToChild(Actor);
}

bool QuadTreeNode::InsertToChild(ALeafActor* Actor)
{
	for (int32 i = 0; i < 4; ++i)
	{
		if (Children[i].IsValid() && Children[i]->Insert(Actor))
		{
			return true;
		}
	}
	return false;
}

bool QuadTreeNode::IntersectsCircle(const FVector& Origin, float Radius) const
{
	const FVector Min(Center.X - Extent.X, Center.Y - Extent.Y, Center.Z);
	const FVector Max(Center.X + Extent.X, Center.Y + Extent.Y, Center.Z + 10.0);
	const FBox Box(Min, Max);
	
	return FMath::SphereAABBIntersection(Origin, Radius * Radius, Box);
}

bool QuadTreeNode::IntersectsRectangle(const FVector& OtherCenter, const FVector& OtherExtent) const
{
	const float DeltaX = FMath::Abs(Center.X - OtherCenter.X);
	const float DeltaY = FMath::Abs(Center.Y - OtherCenter.Y);
	const float SumExtentX = Extent.X + OtherExtent.X;
	const float SumExtentY = Extent.Y + OtherExtent.Y;
	
	return DeltaX <= SumExtentX && DeltaY <= SumExtentY;
}

void QuadTreeNode::CheckInRange(const FVector& QueryCenter, float Radius, bool bParentInRange)
{
	bInRange = bParentInRange && IntersectsCircle(QueryCenter, Radius);
	
	if (!bIsLeaf)
	{
		for (int32 i = 0; i < 4; ++i)
		{
			if (Children[i].IsValid())
			{
				Children[i]->CheckInRange(QueryCenter, Radius, bInRange);
			}
		}
	}
	else
	{
		for (ALeafActor* Actor : Objects)
		{
			if (Actor)
			{
				Actor->Active(Actor->HasCollision(QueryCenter, Radius));
			}
		}
	}
}

bool QuadTreeNode::PointInBounds(const FVector& Point, const FVector& Min, const FVector& Max)
{
	return Point.X >= Min.X && Point.X <= Max.X &&
	       Point.Y >= Min.Y && Point.Y <= Max.Y;
}

void QuadTreeNode::DrawDebug(const UObject* WorldContext) const
{
	if (!WorldContext)
	{
		return;
	}

	const FColor DrawColor = bInRange ? FColor::Green : FColor::Red;
	const FVector DrawCenter = Center + FVector(0, 0, bInRange ? 8.0 : 5.0);
	DrawDebugBox(WorldContext->GetWorld(), DrawCenter, Extent + FVector(0, 0, 1), DrawColor, false, -1.0f, 0, 10.0f);
	
	if (!bIsLeaf)
	{
		for (int32 i = 0; i < 4; ++i)
		{
			if (Children[i].IsValid())
			{
				Children[i]->DrawDebug(WorldContext);
			}
		}
	}
}

bool QuadTreeNode::ReInsert(ALeafActor* Actor)
{
	if (Actor && Insert(Actor))
	{
		return true;
	}
	
	if (Parent.IsValid() && Parent->ReInsert(Actor))
	{
		return true;
	}
	
	EscapeActors.Add(Actor);
	return false;
}

void QuadTreeNode::Update()
{
	if (!bIsLeaf)
	{
		for (int32 i = 0; i < 4; ++i)
		{
			if (Children[i].IsValid())
			{
				Children[i]->Update();
			}
		}
	}
	else
	{
		// 使用反向迭代避免删除时的索引问题
		for (int32 i = Objects.Num() - 1; i >= 0; --i)
		{
			ALeafActor* Actor = Objects[i];
			if (Actor && !IsInBounds(Actor->GetActorLocation()))
			{
				Objects.RemoveAtSwap(i, 1, false);
				
				if (Parent.IsValid())
				{
					Parent->ReInsert(Actor);
				}
				else
				{
					EscapeActors.Add(Actor);
				}
			}
		}
	}
}


