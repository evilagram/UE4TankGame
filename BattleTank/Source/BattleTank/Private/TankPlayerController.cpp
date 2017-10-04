// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

//tick
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("No tank at player controller"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing %s"), *(ControlledTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation;	//get world location through crosshair
	if (GetSightRayHitLocation(HitLocation)) { //has side effect
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		//if hits landscape
			//controlled tank rotates at that point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	// find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	// deproject the screen position of the crosshair to a world direction
	// line trace along that direction and see what we hit (up to a max range)

	return false;
}