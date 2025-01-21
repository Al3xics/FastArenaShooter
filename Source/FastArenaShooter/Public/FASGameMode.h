// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FASGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FASTARENASHOOTER_API AFASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFASGameMode();

protected:
	virtual void BeginPlay() override;

public:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Game Mode Info")
	// UUserWidget* WidgetPlayerInterface;
	//
	// UPROPERTY(EditAnywhere, Category="Game Mode Info")
	// TSubclassOf<UUserWidget> WidgetPlayerInterfaceClass;
};
