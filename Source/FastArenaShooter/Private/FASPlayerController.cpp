// Fill out your copyright notice in the Description page of Project Settings.


#include "FASPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FASCharacterBase.h"
#include "FASEnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AFASPlayerController::AFASPlayerController()
{
}

void AFASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Add Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (!MappingContext.IsNull())
		{
			PlayerSubsystem->AddMappingContext(MappingContext.LoadSynchronous(), 0);
		}
	}

	// Set current health to max health
	CurrentHealth = MaxHealth;
}

void AFASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFASPlayerController::MoveFunc);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AFASPlayerController::JumpFunc);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFASPlayerController::StopJumpingFunc);
	EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFASPlayerController::LookFunc);
	EnhancedInput->BindAction(PossessAction, ETriggerEvent::Triggered, this, &AFASPlayerController::PossessFunc);
	EnhancedInput->BindAction(UnPossessAction, ETriggerEvent::Triggered, this, &AFASPlayerController::PossessFunc);
}

void AFASPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledCharacter = Cast<AFASCharacterBase>(GetPawn());
}

void AFASPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckCanPossess();
}

void AFASPlayerController::MoveFunc(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Move"));

	GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), MovementVector.X);
	GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), MovementVector.Y);
}

void AFASPlayerController::JumpFunc(const FInputActionValue& Value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Jump"));
	
	ControlledCharacter->Jump();
}

void AFASPlayerController::StopJumpingFunc(const FInputActionValue& Value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Jump"));
	
	ControlledCharacter->StopJumping();
}

void AFASPlayerController::LookFunc(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Look"));
	
	GetPawn()->AddControllerYawInput(LookAxisVector.X * MouseSensitivity);
	GetPawn()->AddControllerPitchInput(LookAxisVector.Y * MouseSensitivity);
}

void AFASPlayerController::PossessFunc(const FInputActionValue& Value)
{
	const AFASEnemyBase* Enemy = Cast<AFASEnemyBase>(GetPawn());
	
	// If OtherCharacter is null && not in player, then spawn player
	// Else (OtherCharacter not null), then possess enemy
	if (OtherCharacter == nullptr && Enemy)
	{
		const FVector PlayerSpawnLocation = FVector(Enemy->GetActorLocation() + (Enemy->GetActorForwardVector() * DistanceToFrontSpawn));
		const FRotator PlayerSpawnRotation = FRotator(Enemy->GetActorRotation());
		const FVector PlayerSpawnScale = FVector(Enemy->GetCapsuleComponent()->GetRelativeTransform().GetScale3D());
		const FTransform PlayerTransform = UKismetMathLibrary::MakeTransform(PlayerSpawnLocation, PlayerSpawnRotation, PlayerSpawnScale);
		FActorSpawnParameters* SpawnParams = new FActorSpawnParameters();
		SpawnParams->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		SpawnedPlayerActor = GetWorld()->SpawnActor<AFASPlayer>(MyActorClass, PlayerTransform, *SpawnParams);
		SpawnedPlayerActor->GetCapsuleComponent()->SetVisibility(false, true);
		MoveCameraInDirectionOfPossession(SpawnedPlayerActor);
	}
	else if (OtherCharacter != nullptr)
	{
		bIsPossessingAnyPawn = true;
		MoveCameraInDirectionOfPossession(OtherCharacter);
	}
}

void AFASPlayerController::CheckCanPossess()
{
	if (!bIsPossessingAnyPawn)
	{
		// Used for the LineTrace
		FVector OutLocation;
		FRotator OutRotation;
		ControlledCharacter->GetActorEyesViewPoint(OutLocation, OutRotation);
		const FVector StartLocation = FVector(ControlledCharacter->GetFirstPersonCameraComponent()->GetComponentLocation());
		const FVector EndLocation = FVector(OutLocation + (UKismetMathLibrary::GetForwardVector(OutRotation) * PossessionDistance));
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(ControlledCharacter);
		FHitResult OutHit;
		const bool ValueHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), StartLocation, EndLocation, TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true, FLinearColor::Red, FLinearColor::Green, 0.2f);
	
		if (ValueHit)
		{
			if (AFASCharacterBase* FASCharacterBase = Cast<AFASCharacterBase>(OutHit.GetActor()))
			{
				OtherCharacter = FASCharacterBase;
			}
			else
			{
				OtherCharacter = nullptr;
			}
		}
		else
		{
			OtherCharacter = nullptr;
		}
	}
}

void AFASPlayerController::PossessEnemy()
{
	AActor* Old = GetPawn();
	
	UnPossess();
	Possess(OtherCharacter);
	ControlledCharacter = OtherCharacter;
	bIsPossessingAnyPawn = false;

	if (AFASPlayer* OldFASPlayer = Cast<AFASPlayer>(Old))
	{
		OldFASPlayer->Destroy();
	}
}

void AFASPlayerController::PossessPlayer()
{
	UnPossess();
	Possess(SpawnedPlayerActor);
	SpawnedPlayerActor->GetCapsuleComponent()->SetVisibility(true, true);
}
