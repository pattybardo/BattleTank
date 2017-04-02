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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
		//TODO Tell controlled tank to aim at this point
	}
	
}

//Get world location in linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);

	// De-project the screen position of the crosshair to a world direction
	FVector LookDirection; // OUT variable for unit vector for the look direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
	}

	

	// Line trace along that LookDirection and see what we hit (up to a max range)
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; // Not used
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		LookDirection
	);
}