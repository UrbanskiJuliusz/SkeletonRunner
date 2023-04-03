// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSpawner.generated.h"

class ABaseLevel;

UCLASS()
class SKELETONRUNNER_API ALevelSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void SpawnLevel();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseLevel>> AvailableLevels;

	TArray<ABaseLevel*> LevelList;

private:
	int RandomLevel;
	FVector SpawnLocation = FVector();
	FRotator SpawnRotation = FRotator();
	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
};
