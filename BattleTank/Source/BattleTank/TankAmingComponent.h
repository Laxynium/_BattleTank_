// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAmingComponent.generated.h"

//Enum for aming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel*BarrelToSet, UTankTurret*TurretToSet);

	UFUNCTION(BlueprintCallable, Category="Aiming")
	void AimAt(FVector HitLocation);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatis = EFiringStatus::Aiming;
private:
	UTankBarrel* Barrel=nullptr;
	UTankTurret* Turret = nullptr;
	void moveBarrelToward(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 100000;//Sensible starting value of 1000 m/s
};
