#pragma once

#include "CoreMinimal.h"

class ALeafActor;

/**
 * QuadTree node for spatial partitioning
 * Optimized for cache coherency and minimal allocations
 */
class QuadTreeNode : public TSharedFromThis<QuadTreeNode>
{
public:
	QuadTreeNode(const FVector& InCenter, const FVector& InExtent, TSharedPtr<QuadTreeNode> InParent, int32 InDepth);
	~QuadTreeNode();

	// Core operations
	bool Insert(ALeafActor* Actor);
	void Update();
	void CheckInRange(const FVector& Center, float Radius, bool bParentInRange);
	void DrawDebug(const UObject* WorldContext) const;

	// Query operations
	bool IsInBounds(const FVector& Location) const;
	bool IntersectsCircle(const FVector& Origin, float Radius) const;
	bool IntersectsRectangle(const FVector& OtherCenter, const FVector& OtherExtent) const;

	// Accessors
	FORCEINLINE bool IsLeaf() const { return bIsLeaf; }
	FORCEINLINE int32 GetDepth() const { return Depth; }
	FORCEINLINE const FVector& GetCenter() const { return Center; }
	FORCEINLINE const FVector& GetExtent() const { return Extent; }
	
	TArray<ALeafActor*> EscapeActors;

private:
	// Spatial data - grouped for cache efficiency
	FVector Center;
	FVector Extent;
	
	// Tree structure
	TSharedPtr<QuadTreeNode> Parent;
	TSharedPtr<QuadTreeNode> Children[4];
	
	// Node data
	TArray<ALeafActor*> Objects;
	
	// State flags - packed together
	bool bIsLeaf;
	bool bInRange;
	int32 Depth;
	
	// Configuration
	static constexpr int32 MaxObjectsPerNode = 4;
	
	// Internal operations
	void Subdivide();
	bool InsertToChild(ALeafActor* Actor) const;
	bool ReInsert(ALeafActor* Actor);
	
	// Utility
	static bool PointInBounds(const FVector& Point, const FVector& Min, const FVector& Max);
};
