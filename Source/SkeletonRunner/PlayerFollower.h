// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeadlyObstacle.h"
#include "PlayerFollower.generated.h"

/**
 * 
 */
UCLASS()
class SKELETONRUNNER_API APlayerFollower : public ADeadlyObstacle
{
	GENERATED_BODY()
	
public:
	APlayerFollower();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Statistics")
	int StartSpeed = 300;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Statistics")
	int MaxSpeed = 500;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Statistics")
	float IncreaseVelLoopTime = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Statistics")
	float IncreaseValue = 50.f;

private:
	FTimerHandle IncreaseVelocity_TimerHandle;
	void IncreaseVelocity_TimerEvent();
	int currentVelocity;
};
