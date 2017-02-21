// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto ControlledTank = Cast<ATank>(this->GetPawn());
	auto PlayerTank= Cast<ATank>(this->GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(ControlledTank) || !ensure(PlayerTank))return;

		MoveToActor(PlayerTank, AcceptanceRadius);//TODO check radius is in cm
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();//TODO don't fire every frame
}