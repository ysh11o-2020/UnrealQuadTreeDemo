// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadTreeTargetObject.h"

AQuadTreeTargetObject::AQuadTreeTargetObject()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void AQuadTreeTargetObject::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateMoveDir,this,&ThisClass::UpdateMoveDir,2,true,0.0f);
}

void AQuadTreeTargetObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMovable)
	{
		FVector NewPosRow = GetActorLocation() + FVector(DirXY.X, DirXY.Y, 0) * Speed;
		FVector NewPos = FVector(FMath::Clamp(NewPosRow.X,Bounds.Min.X,Bounds.Max.X),FMath::Clamp(NewPosRow.Y,Bounds.Min.Y,Bounds.Max.Y),NewPosRow.Z);
	
		SetActorLocation(NewPos);
	}
}

void AQuadTreeTargetObject::UpdateMoveDir()
{
	DirXY = FVector2D(FMath::RandRange(-1.0f,1.0f),FMath::RandRange(-1.0f,1.0f));
	Speed = FMath::RandRange(1.0f,5.0f);
}

