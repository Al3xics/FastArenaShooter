// Fill out your copyright notice in the Description page of Project Settings.


#include "FASSpawnerEnemyBase.h"

#include "FASEnemyBase.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"


// Sets default values
AFASSpawnerEnemyBase::AFASSpawnerEnemyBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetLineThickness(5.f);
	SphereCollision->SetSphereRadius(400.f);
	RootComponent = SphereCollision;
}

// Called when the game starts or when spawned
void AFASSpawnerEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFASSpawnerEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFASSpawnerEnemyBase::SpawnEnemy()
{
	FVector RandomSpawnLocation;
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), RandomSpawnLocation, SphereCollision->GetScaledSphereRadius());
	FActorSpawnParameters* SpawnParams = new FActorSpawnParameters();
	SpawnParams->SpawnCollisionHandlingOverride = CollisionHandlingOverride;
	
	GetWorld()->SpawnActor<AFASEnemyBase>(EnemyClassToSpawn, RandomSpawnLocation, FRotator(0, 0, 0), *SpawnParams);
	++TotalEnemy;

	// Stop timer if max enemy reached for this type of enemy
	if (TotalEnemy >= SpawnSettingsEnemy.MaxEnemy)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnerTimerHandle);
	}
	else
	{
		TimeElapsed += GetWorld()->GetDeltaSeconds();
		const float NewSpawnRate = SpawnSettingsEnemy.GetCurrentSpawnRate(TimeElapsed);
		GetWorld()->GetTimerManager().SetTimer(SpawnerTimerHandle, this, &AFASSpawnerEnemyBase::SpawnEnemy, NewSpawnRate, false);
	}

}

