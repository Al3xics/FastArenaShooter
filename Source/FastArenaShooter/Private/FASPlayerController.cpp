// Fill out your copyright notice in the Description page of Project Settings.


#include "FASPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FASCharacterBase.h"
#include "FASEnemyBase.h"
#include "FASGameMode.h"
#include "NavigationSystem.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
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

	GameMode = Cast<AFASGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	// Set current health to max health
	GameMode->CurrentPlayerHealth = GameMode->MaxPlayerHealth;

	GameMode->CheckShouldSpawnEnemyIfPlayerInsideSpawner();
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

	APawn* MyPawn = GetPawn();
	check(MyPawn);

	MyPawn->AddMovementInput(GetPawn()->GetActorForwardVector(), MovementVector.X);
	MyPawn->AddMovementInput(GetPawn()->GetActorRightVector(), MovementVector.Y);
}

void AFASPlayerController::JumpFunc(const FInputActionValue& Value)
{
	ControlledCharacter->Jump();
}

void AFASPlayerController::StopJumpingFunc(const FInputActionValue& Value)
{
	ControlledCharacter->StopJumping();
}

void AFASPlayerController::LookFunc(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	APawn* MyPawn = GetPawn();
	check(MyPawn);
	
	MyPawn->AddControllerYawInput(LookAxisVector.X * MouseSensitivity);
	MyPawn->AddControllerPitchInput(LookAxisVector.Y * MouseSensitivity);
	
}

void AFASPlayerController::PossessFunc(const FInputActionValue& Value)
{
	const AFASEnemyBase* Enemy = Cast<AFASEnemyBase>(GetPawn());

	if (bCanPossessPawn)
	{
		// If   : Player
		// Else : Enemy
		if (OtherCharacter == nullptr && Enemy)
		{
			bCanPossessPawn = false;
			SpawnPlayer(Enemy);
			MoveCameraInDirectionOfPossession(SpawnedPlayerActor, false);
		}
		else if (IsValid(OtherCharacter))
		{
			bCanPossessPawn = false;
			MoveCameraInDirectionOfPossession(OtherCharacter, false);
		}
	}
}

void AFASPlayerController::CheckCanPossess()
{
	if (bCanPossessPawn)
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
	const AFASEnemyBase* Enemy = Cast<AFASEnemyBase>(OtherCharacter);
	if (!Enemy) return;
	
	if (Enemy->CurrentEnemyHealth > 0)
	{
		APawn* Old = GetPawn();
		
		UnPossess();

		if (GameMode && GameMode->EnemyAIControllerClass)
		{
			if (AAIController* AIController = GetWorld()->SpawnActor<AAIController>(GameMode->EnemyAIControllerClass))
			{
				AIController->Possess(Old);
			}
		}
		
		Possess(OtherCharacter);
		
		ControlledCharacter = OtherCharacter;
		bCanPossessPawn = true;

		if (AFASPlayer* OldFASPlayer = Cast<AFASPlayer>(Old))
		{
			OldFASPlayer->Destroy();
		}

		GameMode->CheckShouldSpawnEnemyIfPlayerInsideSpawner();
	}
	else
	{
		SpawnPlayer(Enemy);
		PossessPlayer();
	}
}

void AFASPlayerController::PossessPlayer()
{
	APawn* Old = GetPawn();

	UnPossess();

	if (GameMode && GameMode->EnemyAIControllerClass)
	{
		if (AAIController* AIController = GetWorld()->SpawnActor<AAIController>(GameMode->EnemyAIControllerClass))
		{
			AIController->Possess(Old);
		}
	}

	Possess(SpawnedPlayerActor);
	ControlledCharacter = SpawnedPlayerActor;
	bCanPossessPawn = true;
	SpawnedPlayerActor->GetCapsuleComponent()->SetVisibility(true, true);
	GameMode->CheckShouldSpawnEnemyIfPlayerInsideSpawner();
}

void AFASPlayerController::PossessPlayerAfterEnemyDeath()
{
	const AFASEnemyBase* Enemy = Cast<AFASEnemyBase>(GetPawn());
	
	// If   : Player
	// Else : Enemy
	if (Enemy)
	{
		bCanPossessPawn = false;
		OtherCharacter = nullptr;
		SpawnPlayer(Enemy);
		MoveCameraInDirectionOfPossession(SpawnedPlayerActor, true);
	}
}

void AFASPlayerController::SpawnPlayer(const AFASEnemyBase* Enemy)
{
	FVector TestSpawnLocation = FVector(Enemy->GetActorLocation() + (Enemy->GetActorForwardVector() * DistanceToSpawn));
	TArray<AActor*> ActorsToIgnore;
	FHitResult OutHit;
	Enemy->GetAttachedActors(ActorsToIgnore, true, true);
	const bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), GetPawn()->GetActorLocation(), TestSpawnLocation, ObjectTypesToIgnore, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true, FColor::Red, FColor::Green, 2);
	if (bHit)
	{
		float Distance = FVector::Dist(OutHit.Location, Enemy->GetActorLocation());
		if (Distance < 100.f)
		{
			FVector RandomLocation;
			bool bFoundLocation = UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(GetWorld(), Enemy->GetActorLocation(), RandomLocation, DistanceToSpawn);
			TestSpawnLocation = RandomLocation;
		}
		else
			TestSpawnLocation = OutHit.Location;
	}
	
	FVector PlayerSpawnLocation = TestSpawnLocation;
	const FRotator PlayerSpawnRotation = FRotator(Enemy->GetActorRotation());
	const FVector PlayerSpawnScale = FVector(Enemy->GetCapsuleComponent()->GetRelativeTransform().GetScale3D());
	const FTransform PlayerTransform = UKismetMathLibrary::MakeTransform(PlayerSpawnLocation, PlayerSpawnRotation, PlayerSpawnScale);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	SpawnedPlayerActor = GetWorld()->SpawnActor<AFASPlayer>(MyActorClass, PlayerTransform, SpawnParams);
	SpawnedPlayerActor->GetCapsuleComponent()->SetVisibility(false, true);
}
