// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SkeletonCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class SKELETONRUNNER_API ASkeletonCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* SideViewCamera;

public:
	ASkeletonCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

#pragma region INPUT

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Actions")
		UInputAction* MovementAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Actions")
		UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Mappings")
		UInputMappingContext* BaseMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Mappings")
		int32 BaseMappingPriority = 0;

	void EnhancedMove(const FInputActionValue& Value);

#pragma endregion


public:
	class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCamera; }
	void RestartLevel();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float zCameraPosition;
	FVector tempCameraPos = FVector();
	bool canMove;
};