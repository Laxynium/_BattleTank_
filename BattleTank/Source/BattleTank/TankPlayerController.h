// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
class UTankAimingComponent;
class ATank;
class APawn;
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent*AimCompRef);

private:
	UFUNCTION()
	void onControlledTankDeath();
private:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay()override;

	virtual void SetPawn(APawn* InPawn)override;
	
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector&HitLocation)const;

	bool GetLookDirection(const FVector2D &ScreenLocation, FVector& LookDirection)const;
	bool GetLookVectorHitLocation(const FVector & LookDirection, FVector & HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
};
