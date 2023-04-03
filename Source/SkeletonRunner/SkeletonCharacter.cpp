#include "SkeletonCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DeadlyObstacle.h"
#include "Engine.h"

#include <EnhancedInputComponent.h>

ASkeletonCharacter::ASkeletonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Side View Camera"));
	SideViewCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->JumpZVelocity = 1000.0f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	tempCameraPos = GetActorLocation();
	zCameraPosition = tempCameraPos.Z + 300.0f;
}

void ASkeletonCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASkeletonCharacter::OnOverlapBegin);

	canMove = true;
}

void ASkeletonCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
		}
	}
}

void ASkeletonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	tempCameraPos = GetActorLocation();
	tempCameraPos.X -= 850.0f;
	tempCameraPos.Z = zCameraPosition;
	SideViewCamera->SetWorldLocation(tempCameraPos);
}

void ASkeletonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}

		if (MovementAction)
		{
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASkeletonCharacter::EnhancedMove);
		}
	}
}

void ASkeletonCharacter::EnhancedMove(const FInputActionValue& Value)
{
	if (canMove && Value.GetMagnitude() != 0.0f)
	{
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value[0]);
	}
}

void ASkeletonCharacter::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void ASkeletonCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		ADeadlyObstacle* DeadlyObstacle = Cast<ADeadlyObstacle>(OtherActor);

		if (DeadlyObstacle)
		{
			GetMesh()->Deactivate();
			GetMesh()->SetVisibility(false);

			canMove = false;

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ASkeletonCharacter::RestartLevel, 2.f, false);
		}
	}
}