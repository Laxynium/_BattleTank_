// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed= FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationDelta=RelativeSpeed*this->GetWorld()->DeltaTimeSeconds*MaxDegreesPerSecond;
	auto newRotation = this->RelativeRotation.Yaw + RotationDelta;
	this->SetRelativeRotation(FRotator(0,newRotation,0));
}

