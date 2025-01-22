// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "FASPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FASTARENASHOOTER_API AFASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFASPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn *InPawn) override;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TSoftObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, Category="Player Info")
	ACharacter* ControlledCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Info")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Player Info")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category="Player Infor")
	float MouseSensitivity = 0.5f;

	UFUNCTION()
	void MoveFunc(const FInputActionValue& Value);

	UFUNCTION()
	void JumpFunc(const FInputActionValue& Value);

	UFUNCTION()
	void StopJumpingFunc(const FInputActionValue& Value);

	UFUNCTION()
	void LookFunc(const FInputActionValue& Value);
	
};
