#include "PlayerFollower.h"

APlayerFollower::APlayerFollower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerFollower::BeginPlay()
{
	Super::BeginPlay();
	currentVelocity = StartSpeed;

	GetWorld()->GetTimerManager().SetTimer(IncreaseVelocity_TimerHandle, this, &APlayerFollower::IncreaseVelocity_TimerEvent, IncreaseVelLoopTime, true);
}

void APlayerFollower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + FVector(0, currentVelocity * DeltaTime, 0), true);
}

void APlayerFollower::IncreaseVelocity_TimerEvent()
{
	currentVelocity += IncreaseValue;

	if (currentVelocity >= MaxSpeed)
	{
		GetWorld()->GetTimerManager().ClearTimer(IncreaseVelocity_TimerHandle);
	}
}