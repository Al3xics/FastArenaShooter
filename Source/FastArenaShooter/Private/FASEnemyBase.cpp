﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "FASEnemyBase.h"


// Sets default values
AFASEnemyBase::AFASEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonCameraComponent->SetRelativeLocation(FVector(6,4,85));
}

// Called when the game starts or when spawned
void AFASEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFASEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFASEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

