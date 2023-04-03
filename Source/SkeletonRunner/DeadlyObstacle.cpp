#include "DeadlyObstacle.h"

ADeadlyObstacle::ADeadlyObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADeadlyObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void ADeadlyObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}