// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "TankAmingComponent.h"
#include "TankAIController.h"
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank))return;
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	auto PlayerTank= this->GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(AimingComponent) || !ensure(PlayerTank))return;

		MoveToActor(PlayerTank, AcceptanceRadius);//TODO check radius is in cm
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		AimingComponent->Fire();//TODO don't fire every frame
}