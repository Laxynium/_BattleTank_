// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
class UTankTurret;
class AProjectile;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 100000;//Sensible starting value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

	//local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;//TODO Remove

};
