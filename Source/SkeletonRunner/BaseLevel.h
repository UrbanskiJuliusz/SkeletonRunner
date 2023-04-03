// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseLevel.generated.h"

class UBoxComponent;

UCLASS()
class SKELETONRUNNER_API ABaseLevel : public AActor
{
	GENERATED_BODY()
	
public:
	ABaseLevel();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
	UBoxComponent* Trigger;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
	UBoxComponent* SpawnLocation;

public:
	UBoxComponent* GetTrigger();
	UBoxComponent* GetSpawnLocation();

};
