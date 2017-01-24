// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		ControlledTank->AimAt(GetPlayerTank()->GetTransform().GetLocation());
	}
}

ATank * ATankAIController::GetControlledTank() const
{

	return Cast<ATank>(this->GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning,TEXT("Controlled tank: %s"),*controlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank not set"));
	}
	auto playerTank = GetPlayerTank();
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *playerTank->GetName());
	}
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(this->GetWorld()->GetFirstPlayerController()->GetPawn());
}
