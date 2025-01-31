// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/FASEnemySpawnSettings.h"

float FFASEnemySpawnSettings::GetCurrentSpawnRate(const float TimeElapsed) const
{
	return FMath::Max(InitialSpawnRate - (SpawnRateAcceleration * TimeElapsed), MinSpawnRate);
}
