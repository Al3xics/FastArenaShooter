// Fill out your copyright notice in the Description page of Project Settings.


#include "FASGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AFASGameMode::AFASGameMode()
{
}

void AFASGameMode::BeginPlay()
{
	Super::BeginPlay();

	// CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetPlayerInterface->GetClass());
}
