// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FASCharacterBase.h"
#include "GameFramework/Character.h"
#include "FASEnemyBase.generated.h"

UCLASS()
class FASTARENASHOOTER_API AFASEnemyBase : public AFASCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFASEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
