// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto NewRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
	 
	auto ElevationChange = NewRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	RawNewElevation=FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));

}

