// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possessing a tank"));
	}
	else 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player controller Begin Play"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Player controller possessing: %s"), *(ControlledTank->GetName()));

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


