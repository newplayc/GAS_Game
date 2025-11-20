#include "QuadTreeNode.h"

#include "LeafActor.h"

void QuadTreeNode::Tick(UObject * Obj)
{
	DrawBound(Obj);
	for(const auto & child : Child_Node){
		if(child.IsValid()){
			child->Tick(Obj);
		}
	}
}

QuadTreeNode::QuadTreeNode(const FVector& _center, const FVector& _extend ,TSharedPtr<QuadTreeNode>_root): center(_center),
                                                                                                           extend(_extend) , Root(_root)
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
	return InLoc.X >=center.X - extend.X &&
		InLoc.X <= center.X + extend.X &&
		InLoc.Y >=center.Y - extend.Y &&
		InLoc.Y <= center.Y + extend.Y;
}

void QuadTreeNode::Subdivide()
{
	double x = center.X , y = center.Y , z = center.Z;
	double w = extend.X / 2, h = extend.Y /2 , l = extend.Z;
	Child_Node[0] = (MakeShared<QuadTreeNode>(FVector(x - w  ,y - h ,z) ,
		FVector(w,h,l) , AsShared())  );

	Child_Node[1] = (MakeShared<QuadTreeNode>(FVector(x + w  ,y - h ,z) ,
		FVector(w,h,l),AsShared()) );

	Child_Node[2]=  (MakeShared<QuadTreeNode>(FVector(x - w  ,y + h ,z) ,
		FVector(w,h,l),AsShared()));

	Child_Node[3] = (MakeShared<QuadTreeNode>(FVector(x + w  ,y + h ,z) ,
		FVector(w,h,l) ,AsShared()));
	
	for(const auto & p : Objs)
	{
		InsertToChild(p);
	}
	Objs.Empty();
	isLeaf = false;
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
	for(const auto& child : Child_Node)
	{
		if(child.IsValid() &&  child->Insert(Obj))
		{
			return true;
		}
	}
	return false;
}

bool QuadTreeNode::InterSectWithCircle(const FVector& Orign, float Radius) const 
{
	if(IsInBound(Orign)) return true;
	double CloestX = std::max(center.X - extend.X , std::min(Orign.X  , center.X + extend.X));
	double CloestY = std::max(center.Y - extend.Y , std::min(Orign.Y  , center.Y + extend.Y));
	double DistanceSq = (Orign.X - CloestX) * (Orign.X - CloestX) +
						(Orign.Y - CloestY) * (Orign.Y - CloestY);
	return DistanceSq <= Radius;
}

bool QuadTreeNode::InterSection(const FVector& _pMin, const FVector& _pMax, const FVector& _point)
{		
	return (_point.X >= _pMin.X &&
		_point.X <= _pMax.X &&
		_point.Y >= _pMin.Y &&
		_point.Y <= _pMax.Y);
}

void QuadTreeNode::DrawBound(UObject * Obj) const
{
		FColor drawColor = bInRange ? FColor::Green : FColor::Red;
		FVector drawCenter = center + (bInRange ? FVector(0, 0, 8) : FVector(0, 0, 5));
		DrawDebugBox(Obj ->GetWorld(), drawCenter , extend + FVector(0,0,1) ,drawColor , true,0.3f , 0,2.f);
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
	UE_LOG(LogTemp , Warning , TEXT("Hi This is A Leaf Escape"));
	return false;
}
void QuadTreeNode::update()
{
	if(!isLeaf){
		for(const auto & child : Child_Node){
			if(child.IsValid()){
				child->update();
			}
		}
	}
	else{
		for(const auto & obj : Objs){
			if(!IsInBound(obj->GetActorLocation()))
			{
				if(Root.IsValid())
				{
					Root->ReMatch(obj);
				}
				Objs.Remove(obj);
			}
		}	
	}
	
}


