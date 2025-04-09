// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadTreePlayerController.h"
#include "QuadTreeTargetObject.h"

AQuadTreeTargetObject* AQuadTreePlayerController::GetUnderCursorTargetObject() const
{
	AQuadTreeTargetObject* TargetObject = nullptr;
	FHitResult CursorHitResult;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHitResult);
	if (CursorHitResult.bBlockingHit)
	{
		TargetObject = Cast<AQuadTreeTargetObject>(CursorHitResult.GetActor());
	}
	return TargetObject;
}
