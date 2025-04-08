// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuadTreeTargetObject.h"

/**
 * 
 */
class QUADTREEDEMO_API QuadTreeNode
{
public:
	QuadTreeNode();
	QuadTreeNode(const FVector2D& InPosition, const FVector2D& InSize,const int32 InMaxContainNumber = 4);
	
	~QuadTreeNode();

	FVector2D Position;
	FVector2D Size;

	int32 MaxContainNumber;
	TArray<AQuadTreeTargetObject*> ContainObjects;
	
	TArray<QuadTreeNode*> Children;

	bool bIsLeaf = true;
	bool bIsRoot;

	TSubclassOf<class AActor> ObjectClass = AQuadTreeTargetObject::StaticClass();
	
	bool IsContainedObject(const AQuadTreeTargetObject* InObject) const;

	void InsertObject(AQuadTreeTargetObject* InObject);

	void DrawBoundingBox(const UObject* WorldContextObject) const;

	void DrawSelfAndChildrenBBox(const UObject* WorldContextObject) const;
};
