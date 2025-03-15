// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FASPlayer.h"
#include "GameFramework/GameModeBase.h"
#include "Struct/FASEnemySpawnSettings.h"
#include "FASGameMode.generated.h"

class AFASEnemyBase;
/**
 * 
 */
UCLASS()
class FASTARENASHOOTER_API AFASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFASGameMode();

protected:
	virtual void BeginPlay() override;

public:
	// Enemies
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies")
	TArray<AActor*> SpawnerEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies")
	TSubclassOf<AAIController> EnemyAIControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies")
	float SmoothFocusInterpSpeed = 130.0f;
	
		// Enemy 1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Enemies|Enemy 1")
	float MaxEnemy1Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies|Enemy 1")
	TSubclassOf<AFASEnemyBase> EnemyType1Class;

		// Enemy 2
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Enemies|Enemy 2")
	float MaxEnemy2Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies|Enemy 2")
	TSubclassOf<AFASEnemyBase> EnemyType2Class;

	// Player
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Player")
	float MaxPlayerHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Logic|Player")
	float CurrentPlayerHealth = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Logic|Player")
	bool bIsPlayerDead = false;

	// Weapons
		// Auto Rifle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Weapons|Auto Rifle")
	float AutoRifleDamageEnemyMode = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Weapons|Auto Rifle")
	float AutoRifleDamagePlayerMode = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Weapons|Auto Rifle")
	float AutoRifleDamagePlayerToEnemyHEAD = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Weapons|Auto Rifle")
	float AutoRifleDamagePlayerToEnemyBODY = 10.f;

		// Soul Launcher
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Weapons|Soul Launcher")
	float SoulLauncherDamageEnemyMode = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Weapons|Soul Launcher")
	float SoulLauncherDamagePlayerMode = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Weapons|Soul Launcher")
	float SoulLauncherDamagePlayerToEnemyHEAD = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Weapons|Soul Launcher")
	float SoulLauncherDamagePlayerToEnemyBODY = 10.f;

		// Doll
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Weapons|Doll")
	float DollDamage = 10.f;

	// Revenge Bar
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Revenge Bar")
	float MaxRevenge = 100.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Game Logic|Revenge Bar")
	float CurrentRevenge = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Revenge Bar")
	float RevengeIncrementPerKill = 4.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Revenge Bar")
	float RevengeMultiplier = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Revenge Bar")
	float FallExecutionRevenge = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Revenge Bar")
	float NormalExecutionRevenge = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Revenge Bar")
	float HeadshotExecutionRevenge = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Game Logic|Revenge Bar")
	float UnpossessExecutionRevenge = 10.f;

	// Misc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Misc")
	float FallDeathTime = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Misc")
	float RageHealthBonus = 10.f;

	// Other
	UPROPERTY()
	AFASPlayer* Player = nullptr;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Game Logic")
	bool CheckIsPlayerDead();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Game Logic")
	void DestroyActorAndChildrenActor(AActor* ActorToDestroy);

	UFUNCTION(BlueprintCallable, Category="Game Logic")
	void IncreaseRevenge(float Value);

	UFUNCTION(BlueprintCallable, Category="Game Logic")
	void DecreaseRevengeValue(float Value);

	UFUNCTION(BlueprintCallable, Category="Game Logic")
	void ResetRevengeValue() { CurrentRevenge = 0.f; }

	UFUNCTION()
	void CheckShouldSpawnEnemyIfPlayerInsideSpawner();
};
