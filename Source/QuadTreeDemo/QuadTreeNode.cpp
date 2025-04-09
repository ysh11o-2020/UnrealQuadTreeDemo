// Fill out your copyright notice in the Description page of Project Settings.

#include "QuadTreeNode.h"

#include "Kismet/GameplayStatics.h"

QuadTreeNode::QuadTreeNode(): MaxContainNumber(0), bIsRoot(false)
{
}

QuadTreeNode::QuadTreeNode(const FVector2D& InPosition, const FVector2D& InSize, const int32 InMaxContainNumber):
	bIsRoot(false)
{
	Position = InPosition;
	Size = InSize;
	MaxContainNumber = InMaxContainNumber;
}

QuadTreeNode::~QuadTreeNode()
{
	Children.Empty();
	ContainObjects.Empty();
}

bool QuadTreeNode::IsContainedObject(const AQuadTreeTargetObject* InObject) const
{
	if (InObject == nullptr) return false;
	
	const float MaxX = Position.X + Size.X/2.0f;
	const float MaxY = Position.Y + Size.Y/2.0f;
	const float MinX = Position.X - Size.X/2.0f;
	const float MinY = Position.Y - Size.Y/2.0f;
	
	if ( InObject->GetActorLocation().X > MinX && InObject->GetActorLocation().X < MaxX && InObject->GetActorLocation().Y > MinY && InObject->GetActorLocation().Y < MaxY)
		return true;
	
	return false;
}

void QuadTreeNode::InsertObject(AQuadTreeTargetObject* InObject)
{
	int32 CurObjNum = ContainObjects.Num() + 1;
	ContainObjects.Add(InObject);
	
	if (CurObjNum > MaxContainNumber)
	{
		if (bIsLeaf)
		{
			bIsLeaf = false;
			QuadTreeNode* TLChildNode = new QuadTreeNode(FVector2D(Position.X-Size.X/4,Position.Y+Size.Y/4), Size/2);
			QuadTreeNode* TRChildNode = new QuadTreeNode(FVector2D(Position.X+Size.X/4,Position.Y+Size.Y/4), Size/2);
			QuadTreeNode* BLChildNode = new QuadTreeNode(FVector2D(Position.X-Size.X/4,Position.Y-Size.Y/4), Size/2);
			QuadTreeNode* BRChildNode = new QuadTreeNode(FVector2D(Position.X+Size.X/4,Position.Y-Size.Y/4), Size/2);

			Children.Add(TLChildNode);
			Children.Add(TRChildNode);
			Children.Add(BLChildNode);
			Children.Add(BRChildNode);
			
			for (AQuadTreeTargetObject* Obj : ContainObjects)
			{
				if (TLChildNode->IsContainedObject(Obj)) TLChildNode->InsertObject(Obj);
				if (TRChildNode->IsContainedObject(Obj)) TRChildNode->InsertObject(Obj);
				if (BLChildNode->IsContainedObject(Obj)) BLChildNode->InsertObject(Obj);
				if (BRChildNode->IsContainedObject(Obj)) BRChildNode->InsertObject(Obj);
			}
		}
		else
		{
			for (QuadTreeNode* ChildNode: Children)
			{
				if (ChildNode->IsContainedObject(InObject)) ChildNode->InsertObject(InObject);
			}
		}
	}
	else
	{
		bIsLeaf = true;
	}
}

void QuadTreeNode::DrawBoundingBox(const UObject* WorldContextObject, const FColor DrawColor) const
{
	if (WorldContextObject == nullptr) return;
	
	float DrawHeight = 55.0f;
	float DrawTime = 555/*/UKismetSystemLibrary::GetFrameCount()*/;
	
	DrawDebugLine(WorldContextObject->GetWorld(),FVector(Position.X-Size.X/2,Position.Y-Size.Y/2,DrawHeight),FVector(Position.X-Size.X/2,Position.Y+Size.Y/2,DrawHeight),DrawColor,false,DrawTime,0,5);
	DrawDebugLine(WorldContextObject->GetWorld(),FVector(Position.X-Size.X/2,Position.Y+Size.Y/2,DrawHeight),FVector(Position.X+Size.X/2,Position.Y+Size.Y/2,DrawHeight),DrawColor,false,DrawTime,0,5);
	DrawDebugLine(WorldContextObject->GetWorld(),FVector(Position.X+Size.X/2,Position.Y+Size.Y/2,DrawHeight),FVector(Position.X+Size.X/2,Position.Y-Size.Y/2,DrawHeight),DrawColor,false,DrawTime,0,5);
	DrawDebugLine(WorldContextObject->GetWorld(),FVector(Position.X+Size.X/2,Position.Y-Size.Y/2,DrawHeight),FVector(Position.X-Size.X/2,Position.Y-Size.Y/2,DrawHeight),DrawColor,false,DrawTime,0,5);

	FString DebugStr = FString::Printf(TEXT(" %d "),ContainObjects.Num());
	DrawDebugString(WorldContextObject->GetWorld(),FVector(Position.X,Position.Y,0),DebugStr,nullptr,DrawColor,DrawTime,false,1);

}

void QuadTreeNode::DrawSelfAndChildrenBBox(const UObject* WorldContextObject) const
{
	if (WorldContextObject == nullptr) return;
	if (bIsLeaf)
	{
		DrawBoundingBox(WorldContextObject);
		return;
	}
	else
	{
		for (QuadTreeNode* ChildNode : Children)
		{
			ChildNode->DrawSelfAndChildrenBBox(WorldContextObject);
		}
	}
}

bool QuadTreeNode::IsCircleInterSection(const FVector& CircleCenter, float Radius) const
{
	const float MaxX = Position.X + Size.X/2.0f;
	const float MaxY = Position.Y + Size.Y/2.0f;
	const float MinX = Position.X - Size.X/2.0f;
	const float MinY = Position.Y - Size.Y/2.0f;

	float ClosestX = FMath::Clamp(CircleCenter.X,MinX,MaxX);
	float ClosestY = FMath::Clamp(CircleCenter.Y,MinY,MaxY);
	
	return (ClosestX - CircleCenter.X) * (ClosestX - CircleCenter.X) + (ClosestY - CircleCenter.Y) * (ClosestY - CircleCenter.Y) <= Radius * Radius;
}
