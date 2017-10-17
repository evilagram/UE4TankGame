// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "engine.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	AimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime){
	Super::Tick( DeltaTime );
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank || !AimComp) { return; }
	MoveToActor(PlayerTank, AcceptanceRadius);
	//aim towards the player
	AimComp->AimAt(PlayerTank->GetActorLocation());
	if (AimComp->GetFiringStatus() == EFiringStatus::Locked){
		AimComp->Fire();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// subscribe our local method to tank death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Death Received"))
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
