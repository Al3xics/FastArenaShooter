// Fill out your copyright notice in the Description page of Project Settings.


#include "FASSpawnerEnemyBase.h"

#include "FASEnemyBase.h"
#include "NavigationSystem.h"
#include "Components/BoxComponent.h"
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

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetLineThickness(5);
	BoxCollision->SetBoxExtent(FVector(800, 800, 400));
	BoxCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFASSpawnerEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AFASSpawnerEnemyBase::BeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AFASSpawnerEnemyBase::EndOverlap);

	PlayerController = Cast<AFASPlayerController>(GetWorld()->GetFirstPlayerController());

	if (bIsSentinel)
		SpawnSettingsEnemy.MaxEnemy = 1;
}

// Called every frame
void AFASSpawnerEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFASSpawnerEnemyBase::SpawnEnemy()
{
	if (TotalEnemy < SpawnSettingsEnemy.MaxEnemy)
	{
		FVector RandomSpawnLocation;
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), RandomSpawnLocation, SphereCollision->GetScaledSphereRadius());
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AFASEnemyBase* EnemyBase = GetWorld()->SpawnActor<AFASEnemyBase>(EnemyClassToSpawn, RandomSpawnLocation, FRotator(0, 0, 0), SpawnParams);
		// if (!EnemyBase)
		// 	return;

		EnemyBase->SpawnerWhereEnemySpawned = this;

		if (bIsSentinel)
		{
			EnemyBase->Tags.Add(Tag);
		
			if (Waypoint == nullptr)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("No Waypoint was added to %s"), *GetName()));
			else
				EnemyBase->Waypoint = Waypoint;
		}
		
		++TotalEnemy;
	}

	// Stop timer if max enemy reached for this type of enemy
	if (TotalEnemy >= SpawnSettingsEnemy.MaxEnemy || !IsControlledCharacterInsideBox())
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

void AFASSpawnerEnemyBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (PlayerController && PlayerController->GetPawn() == OtherActor)
	{
		SpawnEnemy();
	}
}

void AFASSpawnerEnemyBase::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;
	
	if (PlayerController && PlayerController->GetPawn() == OtherActor)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnerTimerHandle);
	}
}

bool AFASSpawnerEnemyBase::IsControlledCharacterInsideBox() const
{
	const APawn* ControlledPawn = PlayerController->GetPawn();
	if (!ControlledPawn) return false;

	const bool bIsOverlapping = BoxCollision->IsOverlappingActor(ControlledPawn);

	return bIsOverlapping;
}

