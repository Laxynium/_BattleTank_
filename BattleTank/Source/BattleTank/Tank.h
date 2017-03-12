// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
public:
	virtual float TakeDamage(float DamageAmoumt,struct FDamageEvent const & DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser)override;
	// Return current health as a percentage of a starting health, between 0 and 1
	UFUNCTION(BlueprintPure,Category="Health")
	float GetHealthPercent()const;

	FTankDelegate OnTankDeath;

private:
	ATank();
	virtual void BeginPlay()override;
	UPROPERTY(EditDefaultsOnly,Category= "Setup")
		int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;//Initialize in Begin Play

};
