#pragma once

class ALeafActor;

class QuadTreeNode : public TSharedFromThis<QuadTreeNode>
{
public:
	FVector center;// 中心点
	FVector extend;// 扩展尺寸 // x 半宽  y 半高
	bool isLeaf;
	int32 maxCount = 4;
	int32 Depth = 0;
	TSharedPtr<QuadTreeNode>Root;
	TArray<ALeafActor*>Objs;
	bool bInRange = false;
	static UObject * WorldContext;
	TArray<TSharedPtr<QuadTreeNode>>Child_Node;
	
	TSet<ALeafActor*>EscapeActors;
public:

	void Tick(UObject * Obj);
	
	QuadTreeNode(const FVector& _center, const FVector& _extend , TSharedPtr<QuadTreeNode>_root,int32 _Depth);

	~QuadTreeNode();
	
	// 一个 位置 是否在 当前范围内
	bool IsInBound(const FVector& InLoc) const;
	
	
	// 插入一个 节点
	bool Insert(ALeafActor* Obj);
	
	
	// 与圆形 相交
	bool InterSectWithCircle(const FVector& Orign , float Radius) const;

	// 与矩形相交 
	bool InterSectWithRecentage(const FVector& OtherCenter, const FVector& OtherExtent) const;
	
	void CheckIn(const FVector& _center, float Radious, bool IsParent);
	
	//点是否在指定区域内
	static  bool InterSection(const FVector& _pMin, const FVector& _pMax, const FVector& _point);

	void DrawBound(const UObject * Obj) const;

	void update();
protected:
	//  将这物体 下方孩子节点
	bool InsertToChild(ALeafActor * Obj);
	
	//  细分节点 把孩子向下传递
	void Subdivide();

	bool ReMatch(ALeafActor * Actor);
};
