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
	StartSpawnEnemy();
}

void AFASGameMode::StartSpawnEnemy()
{
	if (bIsPlayerDead) return;
	
	for (AActor* Actor : SpawnerEnemy)
	{
		AFASSpawnerEnemyBase* Spawner = Cast<AFASSpawnerEnemyBase>(Actor);
		if (Spawner)
		{
			switch (Spawner->EnemyType)
			{
				case None:
					UE_LOG(LogTemp, Error, TEXT("No Type was chosen for spawner : %s"), *Spawner->GetName());
					FMessageLog(FName("PIE")).Error(FText::FromString(FString::Printf(TEXT("No Type was chosen for spawner: %s"), *Spawner->GetName())));
					break;
				
				case EnemyType1:
					Spawner->SpawnSettingsEnemy = SpawnSettingsEnemy1;
					Spawner->SpawnEnemy();
					break;
				
				case EnemyType2:
					Spawner->SpawnSettingsEnemy = SpawnSettingsEnemy2;
					Spawner->SpawnEnemy();
					break;
				
				default:
					UE_LOG(LogTemp, Error, TEXT("No Type was chosen for spawner : %s"), *Spawner->GetName());
					FMessageLog(FName("PIE")).Error(FText::FromString(FString::Printf(TEXT("No Type was chosen for spawner: %s"), *Spawner->GetName())));
					break;
			}
		}
	}
}
