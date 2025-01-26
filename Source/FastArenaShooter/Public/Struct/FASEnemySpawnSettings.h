#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FASEnemySpawnSettings.generated.h"

USTRUCT(BlueprintType)
struct FFASEnemySpawnSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Time between spawns in seconds."))
	float InitialSpawnRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Reduced spawn time per second."))
	float SpawnRateAcceleration = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Minimum time between spawns."))
	float MinSpawnRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Minimum time between spawns."))
	int MaxEnemy = 50;
	
	float GetCurrentSpawnRate(const float TimeElapsed) const;
};
