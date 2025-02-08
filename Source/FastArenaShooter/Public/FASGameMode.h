// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
		// Enemy 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies|Enemy 1")
	FFASEnemySpawnSettings SpawnSettingsEnemy1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies|Enemy 1")
	float MaxEnemy1Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies|Enemy 1")
	TSubclassOf<AFASEnemyBase> EnemyType1Class;

		// Enemy 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies|Enemy 2")
	FFASEnemySpawnSettings SpawnSettingsEnemy2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies|Enemy 2")
	float MaxEnemy2Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Enemies|Enemy 2")
	TSubclassOf<AFASEnemyBase> EnemyType2Class;

	// Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic|Player")
	float MaxPlayerHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Logic|Player")
	float CurrentPlayerHealth = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Logic|Player")
	bool bIsPlayerDead = false;
	
	UPROPERTY()
	AFASPlayer* Player = nullptr;

	UFUNCTION(BlueprintCallable, Category="Game Logic")
	void StartSpawnEnemy();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Game Logic")
	bool GetIsPlayerDead();
};
