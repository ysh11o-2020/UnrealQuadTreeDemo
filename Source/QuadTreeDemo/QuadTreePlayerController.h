// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QuadTreePlayerController.generated.h"

class AQuadTreeTargetObject;
/**
 * 
 */
UCLASS()
class QUADTREEDEMO_API AQuadTreePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AQuadTreeTargetObject* GetUnderCursorTargetObject() const;	
};
