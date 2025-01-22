// Fill out your copyright notice in the Description page of Project Settings.


#include "FASPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
}

void AFASPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledCharacter = Cast<ACharacter>(GetPawn());
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
