// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuadTreeNode.h"
#include "GameFramework/GameModeBase.h"
#include "QuadTreeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class QUADTREEDEMO_API AQuadTreeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AQuadTreeGameModeBase();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AQuadTreeTargetObject> QuadTreeTargetObjectClass;

	UPROPERTY(EditAnywhere)
	int32 MaxSpawnNum = 50;

	UPROPERTY(EditAnywhere)
	FBox2D BoundingBox = FBox2D(FVector2D(-10000,-10000),FVector2D(10000,10000));
	
	TSharedPtr<QuadTreeNode> RootNode = nullptr;

	UPROPERTY(VisibleAnywhere)
	TArray<AQuadTreeTargetObject*> TargetObjects;

	void CreateQuadTree();

	UFUNCTION()
	void UpdateQuadTree();
	
	TSharedPtr<QuadTreeNode> GetContainerQuadTreeNode(const AQuadTreeTargetObject* TreeTargetObject) const;

	UPROPERTY()
	FTimerHandle TimerHandle_UpdateQuadTree;
	
};
