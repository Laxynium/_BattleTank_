// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAmingComponent.h"
#include "Tank.h"
#define OUT


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))return;
	FoundAimingComponent(AimingComponent);
}
void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (!InPawn)return;

	auto PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) { return; }

	PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::onControlledTankDeath);
}
void ATankPlayerController::onControlledTankDeath()
{
	StartSpectatingOnly();
	UE_LOG(LogTemp, Warning, TEXT("%s is destroyed"), *GetName());
}
void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn()))return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))return;
	FVector HitLocation(0, 0, 0); //Out parameter
	if (GetSightRayHitLocation(OUT HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector&HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	auto ScreenLocation=FVector2D(ViewportSizeX*CrossHairXLocation,ViewportSizeY*CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}
bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation)const
{
	FHitResult hitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);
	if (this->GetWorld()->LineTraceSingleByChannel(hitResult, StartLocation, EndLocation,ECC_Camera))
	{
		HitLocation=hitResult.Location;
		return true;
	}
	
	HitLocation = { 0,0,0 };
	return false;
}
bool ATankPlayerController::GetLookDirection(const FVector2D &ScreenLocation, FVector& LookDirection) const
{
	FVector CamerWorldLocation/*To be discarded*/;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamerWorldLocation, LookDirection);
}
