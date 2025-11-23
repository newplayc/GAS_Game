#pragma once

// BVH 节点句柄
struct FBVHNodeHandle
{
	uint32 Index;
    
	FBVHNodeHandle() : Index(INDEX_NONE) {}
	explicit FBVHNodeHandle(uint32 InIndex) : Index(InIndex) {}
    
	bool IsValid() const { return Index != INDEX_NONE; }
	bool operator==(const FBVHNodeHandle& Other) const { return Index == Other.Index; }
};

// 节点标记，用于动态更新
enum class EBVHNodeFlags : uint8
{
	None = 0 ,
	Dirty = 1 << 0,      // 需要更新包围盒
	Moving = 1 << 1,       // 正在移动
	RecentlyUpdated = 1 << 2 // 最近更新过
};
ENUM_CLASS_FLAGS(EBVHNodeFlags);

// BVH 节点
struct FBVHNode
{
	FBox Bounds;                    // 世界空间包围盒
	FBVHNodeHandle LeftChild;       // 左子节点
	FBVHNodeHandle RightChild;      // 右子节点
	FBVHNodeHandle Parent;          // 父节点
	TArray<int32> PrimitiveIDs;     // 叶子节点存储的图元ID
	EBVHNodeFlags Flags;            // 节点状态标记
	float LastUpdateTime;           // 最后更新时间
    
	bool IsLeaf() const { return !LeftChild.IsValid() && !RightChild.IsValid(); }
	bool IsRoot() const { return !Parent.IsValid(); }
    
	void MarkDirty() { Flags |= EBVHNodeFlags::Dirty; }
	void ClearDirty() { Flags &= ~EBVHNodeFlags::Dirty; }
	bool IsDirty() const { return !!(Flags & EBVHNodeFlags::Dirty); }
};

// 射线检测结果
struct FBVHRayHit
{
	FVector HitPoint;
	FVector HitNormal;
	float HitDistance;
	int32 PrimitiveID;
    
	FBVHRayHit() : HitDistance(FLT_MAX), PrimitiveID(INDEX_NONE) {}
};

// 分割策略
enum class EBVHSplitStrategy
{
	SAH,            // 表面积启发式（最优）
	EqualCounts,    // 等量分割
	Middle,         // 中点分割
	HLBVH           // 层次化线性BVH
};




class BVH : public  TSharedFromThis<BVH>
{
public:
	BVH();
	~BVH();
    // === 基本操作 ===
    
    // 插入图元
    FBVHNodeHandle InsertPrimitive(int32 PrimitiveID, const FBox& WorldBounds);
    
    // 移除图元
    void RemovePrimitive(FBVHNodeHandle NodeHandle);
    
    // 更新图元包围盒（用于动态物体）
    void UpdatePrimitiveBounds(FBVHNodeHandle NodeHandle, const FBox& NewWorldBounds);
    
    // 标记图元为移动状态
    void MarkPrimitiveAsMoving(FBVHNodeHandle NodeHandle);
    
    // === 动态更新系统 ===
    
    // 增量更新（每帧调用）
    void UpdateDynamicBVH(float DeltaTime);
    
    // 强制完全重构
    void ForceFullRebuild();
    
    // === 查询系统 ===
    
    // 射线检测
    bool Raycast(const FVector& Origin, const FVector& Direction, FBVHRayHit& OutHit) const;
    
    // 范围查询
    void QueryBounds(const FBox& QueryBounds, TArray<int32>& OutPrimitives) const;
    
    // 最近点查询
    bool FindNearestPoint(const FVector& Point, float SearchRadius, FBVHRayHit& OutHit) const;
    
    // === 统计和调试 ===
    
    // 获取统计信息
    void GetStatistics(int32& OutNumNodes, int32& OutNumPrimitives, float& OutBalanceFactor) const;
    
    // 调试绘制
    void DrawDebug(UWorld* World, const FTransform& DrawTransform, float Duration = 0.0f) const;
    
    // 设置分割策略
    void SetSplitStrategy(EBVHSplitStrategy NewStrategy) { SplitStrategy = NewStrategy; }

private:
    // 节点存储
    TArray<FBVHNode> Nodes;
    FBVHNodeHandle RootHandle;
    
    // 动态更新相关
    TSet<FBVHNodeHandle> DirtyNodes;            // 需要更新的节点
    TSet<FBVHNodeHandle> MovingPrimitives;      // 移动中的图元
    TArray<FBVHNodeHandle> NodesToRebalance;    // 需要重新平衡的节点
    
    // 配置参数
    EBVHSplitStrategy SplitStrategy;
    int32 MaxPrimitivesPerLeaf;     // 叶子节点最大图元数
    float RebalanceThreshold;       // 重新平衡阈值
    float LooseFactor;              // 松散包围盒系数
    
    // 统计信息
    int32 PrimitiveCount;
    int32 FrameCounter;
    float TimeSinceLastRebalance;
    
    // === 节点管理 ===
    
    // 分配新节点
    FBVHNodeHandle AllocateNode();
    
    // 释放节点
    void FreeNode(FBVHNodeHandle Handle);
    
    // 递归释放节点树
    void FreeSubtree(FBVHNodeHandle RootHandle);
    
    // === 构建系统 ===
    
    // 构建子树
    FBVHNodeHandle BuildSubtree(TArray<FBVHNodeHandle>&& PrimitiveHandles);
    
    // 分割节点
    void SplitNode(FBVHNodeHandle NodeHandle, TArray<FBVHNodeHandle>&& PrimitiveHandles);
    
    // SAH分割策略
    bool TrySplitWithSAH(const TArray<FBVHNodeHandle>& PrimitiveHandles, 
                        int32& OutSplitAxis, float& OutSplitPosition, 
                        TArray<FBVHNodeHandle>& OutLeft, TArray<FBVHNodeHandle>& OutRight);
    
    // 等量分割
    void SplitEqualCounts(const TArray<FBVHNodeHandle>& PrimitiveHandles,
                         int32 SplitAxis, TArray<FBVHNodeHandle>& OutLeft, 
                         TArray<FBVHNodeHandle>& OutRight);
    
    // === 动态更新系统 ===
    
    // 自底向上更新节点包围盒
    void RefitNode(FBVHNodeHandle NodeHandle);
    
    // 检查并重新平衡子树
    void CheckAndRebalanceSubtree(FBVHNodeHandle NodeHandle);
    
    // 重新构建子树
    void RebuildSubtree(FBVHNodeHandle NodeHandle);
    
    // 计算节点平衡因子
    float CalculateNodeBalanceFactor(FBVHNodeHandle NodeHandle) const;
    
    // === 查询系统 ===
    
    // 递归射线检测
    bool RaycastNode(FBVHNodeHandle NodeHandle, const FVector& Origin, 
                    const FVector& Direction, FBVHRayHit& OutHit) const;
    
    // 递归范围查询
    void QueryNode(FBVHNodeHandle NodeHandle, const FBox& QueryBounds, 
                  TArray<int32>& OutPrimitives) const;
    
    // 辅助函数：计算包围盒的中心点
    FVector CalculateBoundsCenter(const TArray<FBVHNodeHandle>& PrimitiveHandles) const;
    
    // 辅助函数：计算合并包围盒
    FBox CalculateMergedBounds(const TArray<FBVHNodeHandle>& PrimitiveHandles) const;
    
    // SAH 成本计算
    float CalculateSAHCost(int32 LeftCount, const FBox& LeftBounds,
                          int32 RightCount, const FBox& RightBounds) const;


	template<typename T>
	FORCEINLINE static T  GetSurfaceArea(const FBox& Box) 
	{
		UE::Math::TVector<T> Size = Box.Max - Box.Min;
		return 0.5f * (Size.X * Size.Y + Size.X * Size.Z + Size.Y * Size.Z);
	}

};



