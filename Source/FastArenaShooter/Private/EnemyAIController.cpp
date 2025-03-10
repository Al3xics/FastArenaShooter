// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "FASEnemyBase.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemyAIController::AEnemyAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AFASGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	Super::UpdateControlRotation(DeltaTime, false);

	//Smooth and change the pawn rotation
	if (bUpdatePawn)
	{
		//Get pawn
		APawn* const MyPawn = GetPawn();

		if (Cast<AFASEnemyBase>(MyPawn))
		{
			//Get Pawn current rotation
			const FRotator CurrentPawnRotation = MyPawn->GetActorRotation();
 
			//Calculate smoothed rotation
			SmoothTargetRotation = UKismetMathLibrary::RInterpTo_Constant(MyPawn->GetActorRotation(), ControlRotation, DeltaTime, GameMode->SmoothFocusInterpSpeed);
			//Check if we need to change
			if (CurrentPawnRotation.Equals(SmoothTargetRotation, 1e-3f) == false)
			{
				//Change rotation using the Smooth Target Rotation
				MyPawn->FaceRotation(SmoothTargetRotation, DeltaTime);
			}
		}
	}
}

