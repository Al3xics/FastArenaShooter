// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FASCharacterBase.h"
#include "FASPlayer.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "FASPlayerController.generated.h"

class AFASPlayer;
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

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TSoftObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* PossessAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* UnPossessAction;

	UPROPERTY(VisibleAnywhere, Category="Player Info")
	AFASCharacterBase* ControlledCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Info")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Player Info")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category="Player Info")
	float MouseSensitivity = 0.5f;

	UPROPERTY(EditAnywhere, Category="Player Info")
	float PossessionDistance = 1000.f;

	UPROPERTY(VisibleAnywhere, Category="Player Info")
	AFASCharacterBase* OtherCharacter = nullptr;

	UPROPERTY(EditAnywhere, Category="Player Info")
	float DistanceToFrontSpawn = 300.0f;

	UPROPERTY(EditAnywhere, Category="Player Info")
	TSubclassOf<AFASPlayer> MyActorClass = AFASPlayer::StaticClass();

	UPROPERTY()
	bool bIsPossessingAnyPawn = false;

	UFUNCTION()
	void MoveFunc(const FInputActionValue& Value);

	UFUNCTION()
	void JumpFunc(const FInputActionValue& Value);

	UFUNCTION()
	void StopJumpingFunc(const FInputActionValue& Value);

	UFUNCTION()
	void LookFunc(const FInputActionValue& Value);

	UFUNCTION()
	void PossessFunc(const FInputActionValue& Value);

	UFUNCTION()
	void CheckCanPossess();

	UFUNCTION(BlueprintCallable, Category="Controller")
	void PossessPawn();

	UFUNCTION(BlueprintCallable, Category="Controller")
	void UnPossessPawn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Camera")
	void MoveCameraInDirectionOfPossession(AFASCharacterBase* PawnToPossess);
	
};
