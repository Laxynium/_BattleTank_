// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

ATank * ATankAIController::getControlledTank() const
{

	return Cast<ATank>(this->GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = getControlledTank();
	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning,TEXT("Controlled tank: %s"),*controlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank not set"));
	}
	auto playerTank = getPlayerTank();
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *playerTank->GetName());
	}
}

ATank * ATankAIController::getPlayerTank() const
{
	return Cast<ATank>(this->GetWorld()->GetFirstPlayerController()->GetPawn());
}
