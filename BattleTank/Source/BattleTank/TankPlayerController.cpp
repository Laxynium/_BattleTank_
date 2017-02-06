// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"
#define OUT


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();
	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player pawn tank: %s"), *controlledTank->GetName());
	}
}
void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{

	if (!GetControlledTank())return;

	FVector HitLocation(0, 0, 0); //Out parameter
	if (GetSightRayHitLocation(OUT HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector&HitLocation) const
{
	auto tank = GetControlledTank();
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	auto ScreenLocation=FVector2D(ViewportSizeX*CrossHairXLocation,ViewportSizeY*CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			return true;
			//UE_LOG(LogTemp, Warning, TEXT("Look location: %s"), *HitLocation.ToString());
		}
	}
	return false;
}
bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation)const
{
	FHitResult hitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);
	if (this->GetWorld()->LineTraceSingleByChannel(hitResult, StartLocation, EndLocation,ECC_Visibility))
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


