﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "FASPlayer.h"

#include "Components/CapsuleComponent.h"


// Sets default values
AFASPlayer::AFASPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.7, 0.7, 0.7));
}

// Called when the game starts or when spawned
void AFASPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFASPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFASPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

