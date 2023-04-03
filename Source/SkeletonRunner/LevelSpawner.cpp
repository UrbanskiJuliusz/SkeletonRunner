#include "LevelSpawner.h"

#include "BaseLevel.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

ALevelSpawner::ALevelSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnLevel();
	SpawnLevel();
	SpawnLevel();
}

void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelSpawner::SpawnLevel()
{
	SpawnLocation = FVector(0.0f, 1000.0f, 0.0f);
	SpawnRotation = FRotator(0.f, 90.f, 0.f);

	if (LevelList.Num() > 0)
	{
		ABaseLevel* LastLevel = LevelList.Last();
		SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	RandomLevel = FMath::RandRange(0, (AvailableLevels.Num() - 1));
	ABaseLevel* NewLevel = nullptr;

	NewLevel = GetWorld()->SpawnActor<ABaseLevel>(AvailableLevels[RandomLevel], SpawnLocation, SpawnRotation, SpawnParameters);

	if (NewLevel)
	{
		if (NewLevel->GetTrigger())
		{
			NewLevel->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawner::OnOverlapBegin);
		}
	}

	LevelList.Add(NewLevel);

	if (LevelList.Num() > 5)
	{
		LevelList[0]->Destroy();
		LevelList.RemoveAt(0);
	}
}

void ALevelSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel();

	if (OtherActor != nullptr)
		OverlappedComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

