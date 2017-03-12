// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "TankAmingComponent.h"
#include "TankAIController.h"
#include "Tank.h"
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
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
		
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (!InPawn)return;
	
	auto PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) { return; }

	PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::onControlledTankDeath);
	//Sbscribe our local method to the tank's death event
}

void ATankAIController::onControlledTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("%s is destroyed"), *GetName());
}
