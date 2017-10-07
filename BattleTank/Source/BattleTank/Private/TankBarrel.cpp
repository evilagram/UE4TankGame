// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	//move barrel the right amount this frame
	//given a max elevation speed, and the frame time
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(RawNewElevation,0,0));
}

