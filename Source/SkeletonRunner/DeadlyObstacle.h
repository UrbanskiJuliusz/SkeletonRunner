// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadlyObstacle.generated.h"

UCLASS()
class SKELETONRUNNER_API ADeadlyObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	ADeadlyObstacle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
