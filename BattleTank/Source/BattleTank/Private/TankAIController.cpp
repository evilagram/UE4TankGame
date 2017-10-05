// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "engine.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("No tank at AI controller"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller possessing %s"), *(ControlledTank->GetName()));
	}
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot Detect Player from AI"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI %s detects Player %s"), *(ControlledTank->GetName()), *(PlayerTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn) {
		return Cast<ATank>(PlayerPawn);
	}
	else {
		return nullptr;
	}
}

void ATankAIController::Tick(float DeltaTime){
	Super::Tick( DeltaTime );
	if (GetPlayerTank()) {
		if (GetControlledTank()) {
			GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		}
	}
}