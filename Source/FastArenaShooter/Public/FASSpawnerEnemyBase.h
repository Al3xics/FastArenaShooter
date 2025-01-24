// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FASEnemyBase.h"
#include "GameFramework/Actor.h"
#include "FASSpawnerEnemyBase.generated.h"

UCLASS()
class FASTARENASHOOTER_API AFASSpawnerEnemyBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFASSpawnerEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	TSubclassOf<AFASEnemyBase> EnemyClassToSpawn;
	
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnEnemy();
};
