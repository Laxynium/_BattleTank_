// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank1.h"


// Sets default values
ATank1::ATank1()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank1::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATank1::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

