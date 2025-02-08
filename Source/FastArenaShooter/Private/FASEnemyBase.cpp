// Fill out your copyright notice in the Description page of Project Settings.


#include "FASEnemyBase.h"

#include "FASPlayerController.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFASEnemyBase::AFASEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonCameraComponent->SetRelativeLocation(CameraRelativeLocationInGame);
}

// Called when the game starts or when spawned
void AFASEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AFASPlayerController>(GetWorld()->GetFirstPlayerController());

	GameMode = Cast<AFASGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	// Set current health to max health
	if (IsA(GameMode->EnemyType1Class))
	{
		MaxEnemyHealth = GameMode->MaxEnemy1Health;
		CurrentEnemyHealth = GameMode->MaxEnemy1Health;
	}
	else if (IsA(GameMode->EnemyType2Class))
	{
		MaxEnemyHealth = GameMode->MaxEnemy2Health;
		CurrentEnemyHealth = GameMode->MaxEnemy2Health;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("Please choose a class for EnemyTypeClass in the GameMode."));
	}
}

// Called every frame
void AFASEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Force Camera position because when unpossessing enemy when moving, camera does not reset correctly
	if (!PlayerController->bCanPossessPawn && // If we are not playing possess animation (move camera to character)
		FirstPersonCameraComponent->GetRelativeLocation() != CameraRelativeLocationInGame)
	{
		FirstPersonCameraComponent->SetRelativeLocation(CameraRelativeLocationInGame);
	}
}

// Called to bind functionality to input
void AFASEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

