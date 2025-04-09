// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadTreeGameModeBase.h"
#include "QuadTreePlayerController.h"

AQuadTreeGameModeBase::AQuadTreeGameModeBase()
{
	TargetObjects.Empty();

	PlayerControllerClass = AQuadTreePlayerController::StaticClass();
}

void AQuadTreeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	check(QuadTreeTargetObjectClass);
	
	for (int32 i=0;i<MaxSpawnNum;i++)
	{
		FVector SpawnLocation = FVector(FMath::RandRange(BoundingBox.Min.X, BoundingBox.Max.X),FMath::RandRange(BoundingBox.Min.Y,BoundingBox.Max.Y),50.0f);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		if (AQuadTreeTargetObject* QuadTreeTargetObject = GetWorld()->SpawnActor<AQuadTreeTargetObject>(QuadTreeTargetObjectClass,SpawnLocation,FRotator::ZeroRotator,SpawnParams))
		{
			TargetObjects.Add(QuadTreeTargetObject);
			UE_LOG(LogTemp,Warning,TEXT("[AQuadTreeGameModeBase::BeginPlay] Spawn %s at (%f,%f,%f)"),
					*QuadTreeTargetObject->GetName(),
					SpawnLocation.X,SpawnLocation.Y,SpawnLocation.Z);
		}
	}
	CreateQuadTree();
	RootNode->DrawSelfAndChildrenBBox(this);

	for (AQuadTreeTargetObject* QuadTreeTarget : TargetObjects)
	{
		QuadTreeNode* TempNode = GetContainerQuadTreeNode(QuadTreeTarget);
		//UE_LOG(LogTemp,Warning,TEXT("* %s contain [%f,%f]*"),*QuadTreeTarget->GetName(),TempNode->Position.X,TempNode->Position.Y);
		TempNode->DrawBoundingBox(this,FColor::Orange);
	}
}

QuadTreeNode* AQuadTreeGameModeBase::GetRootNode() const
{
	return RootNode;
}

void AQuadTreeGameModeBase::CreateQuadTree()
{
	if (RootNode == nullptr)
	{
		FVector2D RootPosition = (BoundingBox.Min + BoundingBox.Max)/2;
		FVector2D RootSize = BoundingBox.Max - BoundingBox.Min;
		RootNode = new QuadTreeNode(RootPosition,RootSize);
	}
	RootNode->bIsRoot = true;
	
	for (AQuadTreeTargetObject* QuadTreeTarget : TargetObjects)
	{
		if (RootNode->IsContainedObject(QuadTreeTarget))
		{
			RootNode->InsertObject(QuadTreeTarget);
		}
	}
}

void AQuadTreeGameModeBase::UpdateQuadTree()
{
	
}

QuadTreeNode* AQuadTreeGameModeBase::GetContainerQuadTreeNode(AQuadTreeTargetObject* TreeTargetObject) const
{
	QuadTreeNode* SearchNode = RootNode;
	while (SearchNode != nullptr && !SearchNode->bIsLeaf)
	{
		if (!RootNode->IsContainedObject(TreeTargetObject)) return nullptr;
		else
		{
			for (QuadTreeNode* ChildNode:SearchNode->Children)
			{
				if (ChildNode->IsContainedObject(TreeTargetObject))
				{
					SearchNode = ChildNode;
					break;
				}
			}
		}
	}
	return SearchNode;
}

