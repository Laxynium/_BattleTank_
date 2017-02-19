// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAmingComponent.generated.h"

//Enum for aming state
UENUM()
enum class EFiringStatus : uint8
{
	Aiming,
	Reloading,
	Locked
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAmingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAmingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel*BarrelToSet, UTankTurret*TurretToSet);

	void AimAt(FVector HitLocation,float LaunchSpeed);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatis = EFiringStatus::Aiming;
private:
	UTankBarrel* Barrel=nullptr;
	UTankTurret* Turret = nullptr;

	void moveBarrelToward(FVector AimDirection);
	
};
