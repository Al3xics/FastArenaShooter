// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FASGameMode.h"
#include "EnemyAIController.generated.h"

UCLASS()
class FASTARENASHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AFASGameMode* GameMode;

	FRotator SmoothTargetRotation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn) override;
};
