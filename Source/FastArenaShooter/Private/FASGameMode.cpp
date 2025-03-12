// Fill out your copyright notice in the Description page of Project Settings.


#include "FASGameMode.h"
#include "FASSpawnerEnemyBase.h"
#include "Logging/MessageLog.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AFASGameMode::AFASGameMode()
{
}

void AFASGameMode::BeginPlay()
{
	Super::BeginPlay();
	
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
