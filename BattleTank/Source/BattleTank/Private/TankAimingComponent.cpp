// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this,OutLaunchVelocity,StartLocation,HitLocation,LaunchSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace)) {
		//Calculate Launch Velocity
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel->Elevate(5); called"), Time)
		MoveBarrelTowards(AimDirection);
	}
	else {
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No Solution Found"), Time)
	}


}

void UTankAimingComponent::SetBarrelComponent(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretComponent(UTankTurret* TurretToSet) {
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	//work out difference between current barrel rotation and air direction
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch); //remove magic number

	//work out difference between current turret rotation and air direction
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	DeltaRotator = AimAsRotator - TurretRotation;
	Turret->RotateTurret(DeltaRotator.Yaw);
}