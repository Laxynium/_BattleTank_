// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAmingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAmingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAmingComponent();
	void SetBarrelReference(UTankBarrel * BarrelToSet);
	void SetTurretReference(UTankTurret * TurretToSet);
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AimAt(FVector HitLocation,float LaunchSpeed);
protected:
	void moveBarrelToward(FVector AimDirection);
	void rotateTurret(FVector AimDirection);
private:
	UTankBarrel* Barrel=nullptr;
	UTankTurret* Turret = nullptr;
	
};
