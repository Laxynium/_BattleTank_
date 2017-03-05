// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,Category="Setup")//Consider EditDefaultsOnly
	float AcceptanceRadius = 8000;
private:
	virtual void Tick(float DeltaSeconds) override;
	
};
