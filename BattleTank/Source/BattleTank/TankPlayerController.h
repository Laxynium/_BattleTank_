// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank()const;

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay()override;

	
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector&HitLocation)const;

	bool GetLookDirection(const FVector2D &ScreenLocation, FVector& LookDirection)const;
	bool GetLookVectorHitLocation(const FVector & LookDirection, FVector & HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	
};
