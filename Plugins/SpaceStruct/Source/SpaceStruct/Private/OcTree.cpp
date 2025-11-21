#include "OcTree.h"

#include "LeafActor.h"


OcTree::OcTree(const FVector& InCenter, const FVector& InExtent, const TSharedPtr<OcTree>& InParent, int32 InDepth)
: Center(InCenter) , Extent(InExtent) ,Parent(InParent) , bIsLeaf(true) , bInRange(false) , Depth(InDepth)
{
	Objects.Reserve(MaxObjectsPerNode);
	for (int32 i = 0; i < MaxObjectsPerNode; ++i)
	{
		Children[i] = nullptr;
	}
}

OcTree::~OcTree()
{
	Objects.Empty();
	for(int32 i =0; i < MaxObjectsPerNode; ++i)
	{
		Children[i].Reset();
	}
}

bool OcTree::Insert(ALeafActor* Actor)
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

void OcTree::Update()
{
	if (!bIsLeaf)
	{
		for (int32 i = 0; i < MaxObjectsPerNode; ++i)
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
					EscapeActors.AddUnique(Actor);
				}
			}
		}
	}
}

void OcTree::CheckInRange(const FVector& Orign, float Radius, bool bParentInRange)
{
	bInRange = bParentInRange && IntersectsCircle(Orign, Radius);
	
	if (!bIsLeaf)
	{
		for (int32 i = 0; i < MaxObjectsPerNode; ++i)
		{
			if (Children[i].IsValid())
			{
				Children[i]->CheckInRange(Orign, Radius, bInRange);
			}
		}
	}
	else
	{
		for (ALeafActor* Actor : Objects)
		{
			if (Actor)
			{
				Actor->Active(Actor->HasCollision(Orign, Radius));
			}
		}
	}
}

void OcTree::DrawDebug(const UObject* WorldContext) const
{
	if (!WorldContext)
	{
		return;
	}

	const FColor DrawColor = bInRange ? FColor::Green : FColor::Red;
	DrawDebugBox(WorldContext->GetWorld(), Center, Extent , DrawColor, false, -1.0f, 0, 5.0f);
	if (!bIsLeaf)
	{
		for (int32 i = 0; i < MaxObjectsPerNode; ++i)
		{
			if (Children[i].IsValid())
			{
				Children[i]->DrawDebug(WorldContext);
			}
		}
	}
}

bool OcTree::IsInBounds(const FVector& Location) const
{
	return FMath::Abs(Location.X - Center.X) <= Extent.X &&
		FMath::Abs(Location.Y - Center.Y) <= Extent.Y &&
		FMath::Abs(Location.Z - Center.Z) <= Extent.Z;
}




bool OcTree::IntersectsCircle(const FVector& Origin, float Radius) const
{
	const FVector Min(Center.X - Extent.X, Center.Y - Extent.Y, Center.Z - Extent.Z);
	const FVector Max(Center.X + Extent.X, Center.Y + Extent.Y, Center.Z + Extent.Z);
	const FBox Box(Min, Max);
	
	return FMath::SphereAABBIntersection(Origin, static_cast<double>(Radius) * Radius, Box);
}

bool OcTree::IntersectsRectangle(const FVector& OtherCenter, const FVector& OtherExtent) const
{
	const float DeltaX = FMath::Abs(Center.X - OtherCenter.X);
	const float DeltaY = FMath::Abs(Center.Y - OtherCenter.Y);
	const float DeltaZ = FMath::Abs(Center.Z - OtherCenter.Z);
	
	const float SumExtentX = Extent.X + OtherExtent.X;
	const float SumExtentY = Extent.Y + OtherExtent.Y;
	const float SumExtentZ = Extent.Z + OtherExtent.Z;
	return DeltaX <= SumExtentX && DeltaY <= SumExtentY && DeltaZ <= SumExtentZ;
}

void OcTree::Subdivide()
{
	bIsLeaf = false;
	
	const double HalfX = Extent.X * 0.5;
	const double HalfY = Extent.Y * 0.5;
	const double HalfZ = Extent.Z * 0.5;
	const FVector ChildExtent(HalfX, HalfY, HalfZ);
	
	//8 个 子节点
	Children[0] = MakeShared<OcTree>(FVector(Center.X - HalfX, Center.Y - HalfY, Center.Z - HalfZ), ChildExtent, AsShared(), Depth + 1);
	Children[1] = MakeShared<OcTree>(FVector(Center.X - HalfX, Center.Y - HalfY, Center.Z + HalfZ), ChildExtent, AsShared(), Depth + 1);
	Children[2] = MakeShared<OcTree>(FVector(Center.X - HalfX, Center.Y + HalfY, Center.Z - HalfZ), ChildExtent, AsShared(), Depth + 1);
	Children[3] = MakeShared<OcTree>(FVector(Center.X - HalfX, Center.Y + HalfY, Center.Z + HalfZ), ChildExtent, AsShared(), Depth + 1);
	Children[4] = MakeShared<OcTree>(FVector(Center.X + HalfX, Center.Y - HalfY, Center.Z - HalfZ), ChildExtent, AsShared(), Depth + 1);
	Children[5] = MakeShared<OcTree>(FVector(Center.X + HalfX, Center.Y - HalfY, Center.Z + HalfZ), ChildExtent, AsShared(), Depth + 1);
	Children[6] = MakeShared<OcTree>(FVector(Center.X + HalfX, Center.Y + HalfY, Center.Z - HalfZ), ChildExtent, AsShared(), Depth + 1);
	Children[7] = MakeShared<OcTree>(FVector(Center.X + HalfX, Center.Y + HalfY, Center.Z + HalfZ), ChildExtent, AsShared(), Depth + 1);
	
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
				EscapeActors.AddUnique(Actor);
			}
		}
	}
	
	Objects.Empty();
}

bool OcTree::InsertToChild(ALeafActor* Actor) const
{
	for (int32 i = 0; i < MaxObjectsPerNode; ++i)
	{
		if (Children[i].IsValid() && Children[i]->Insert(Actor))
		{
			return true;
		}
	}
	return false;
}

bool OcTree::ReInsert(ALeafActor* Actor)
{
	if (Actor && Insert(Actor))
	{
		return true;
	}
	
	if (Parent.IsValid() && Parent->ReInsert(Actor))
	{
		return true;
	}
	
	EscapeActors.AddUnique(Actor);
	return false;
}

bool OcTree::PointInBounds(const FVector& Point, const FVector& Min, const FVector& Max)
{
	return Point.X >= Min.X && Point.X <= Max.X &&
	   Point.Y >= Min.Y && Point.Y <= Max.Y &&
	   	Point.Z >= Min.Z && Point.Z  <= Max.Z;
}
