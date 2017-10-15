// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "engine.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	AimComp = Cast<ATank>(GetPawn())->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime){
	Super::Tick( DeltaTime );
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(PlayerTank && AimComp)) { return; }
	MoveToActor(PlayerTank, AcceptanceRadius);
	//aim towards the player
	AimComp->AimAt(PlayerTank->GetActorLocation());
	if (AimComp->GetFiringStatus() == EFiringStatus::Locked){
		AimComp->Fire();
	}
}