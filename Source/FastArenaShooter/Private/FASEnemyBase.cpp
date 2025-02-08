// Fill out your copyright notice in the Description page of Project Settings.


#include "FASEnemyBase.h"

#include "FASPlayerController.h"


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

