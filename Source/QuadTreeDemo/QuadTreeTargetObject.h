// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuadTreeTargetObject.generated.h"

UCLASS()
class QUADTREEDEMO_API AQuadTreeTargetObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuadTreeTargetObject();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	bool bMovable = false;
	
	UPROPERTY(VisibleAnywhere)
	float Speed = 3.0f;
	
	UPROPERTY(VisibleAnywhere)
	FVector2D DirXY = FVector2D::ZeroVector;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle TimerHandle_UpdateMoveDir;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBox2f Bounds = FBox2f(FVector2f(-10000.0f,-10000.0f),FVector2f(10000.0f,10000.0f));
	
	UFUNCTION()
	void UpdateMoveDir();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
