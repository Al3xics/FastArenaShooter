// Fill out your copyright notice in the Description page of Project Settings.


#include "FASGameMode.h"
#include "FASSpawnerEnemyBase.h"
#include "Logging/MessageLog.h"

#include "Kismet/GameplayStatics.h"

AFASGameMode::AFASGameMode()
{
}

void AFASGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFASSpawnerEnemyBase::StaticClass(), SpawnerEnemy);
	bIsPlayerDead = false;
}

bool AFASGameMode::CheckIsPlayerDead()
{
	if (CurrentPlayerHealth <= 0){
		bIsPlayerDead = true;
	}

	return bIsPlayerDead;
}

void AFASGameMode::IncreaseRevenge(const float Value)
{
	CurrentRevenge = FMath::Clamp(CurrentRevenge + Value, 0, MaxRevenge);
}

void AFASGameMode::DecreaseRevengeValue(const float Value)
{
	CurrentRevenge = FMath::Clamp(CurrentRevenge - Value, 0, MaxRevenge);
}

void AFASGameMode::CheckShouldSpawnEnemyIfPlayerInsideSpawner()
{
	for (AActor* Actor : SpawnerEnemy)
	{
		AFASSpawnerEnemyBase* Spawner = Cast<AFASSpawnerEnemyBase>(Actor);
		if (Spawner->IsControlledCharacterInsideBox())
			Spawner->SpawnEnemy();
	}
}
