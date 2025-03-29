// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FASPlayerController.h"
#include "GameFramework/Actor.h"
#include "Enum/FASEnemyType.h"
#include "Struct/FASEnemySpawnSettings.h"
#include "FASSpawnerEnemyBase.generated.h"

class AFASEnemyBase;

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
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner", meta = (ToolTip="If IsSentinel is true, 'MaxEnemy' will be set to 1."))
	FFASEnemySpawnSettings SpawnSettingsEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	TSubclassOf<AFASEnemyBase> EnemyClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	TEnumAsByte<EEnemyType> EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner", meta = (ToolTip="Tag used only if IsSentinel is true. Will be used to affect the behaviour tree corresponding to sentinel mode."))
	FName Tag = "Sentinel";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	bool bIsSentinel = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawner")
	AActor* Waypoint;

	UPROPERTY()
	FTimerHandle SpawnerTimerHandle;

	UPROPERTY(VisibleAnywhere)
	float TimeElapsed = 0.0f;

	UPROPERTY()
	int TotalEnemy = 0;

	UPROPERTY()
	AFASPlayerController* PlayerController;
	
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnEnemy();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	bool IsControlledCharacterInsideBox() const;
};
