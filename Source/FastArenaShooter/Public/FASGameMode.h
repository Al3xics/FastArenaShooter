// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FASPlayer.h"
#include "GameFramework/GameModeBase.h"
#include "Struct/FASEnemySpawnSettings.h"
#include "FASGameMode.generated.h"

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
	// Enemy 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic")
	FFASEnemySpawnSettings SpawnSettingsEnemy1;

	// Enemy 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic")
	FFASEnemySpawnSettings SpawnSettingsEnemy2;

	// Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Logic")
	float MaxPlayerHealth = 100.f;

	static float CurrentPlayerHealth;
	
	UPROPERTY()
	AFASPlayer* Player = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Logic")
	bool bIsPlayerDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Logic")
	TArray<AActor*> SpawnerEnemy;

	UFUNCTION(BlueprintCallable, Category="Game Logic")
	void StartSpawnEnemy();
};
