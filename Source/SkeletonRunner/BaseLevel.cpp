#include "BaseLevel.h"

#include "Components/BoxComponent.h"

ABaseLevel::ABaseLevel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseLevel::BeginPlay()
{
	Super::BeginPlay();
	
	if (Trigger != nullptr)
		Trigger->bHiddenInGame = true;
}

void ABaseLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBoxComponent* ABaseLevel::GetTrigger()
{
	return Trigger;
}

UBoxComponent* ABaseLevel::GetSpawnLocation()
{
	return SpawnLocation;
}

