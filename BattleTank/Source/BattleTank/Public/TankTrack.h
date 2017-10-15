// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set Maximum Driving Force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 40000000;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:
	UTankTrack();

	void DriveThrottle();

	void ApplySidewaysForce();

	// Called when the game starts
	virtual void BeginPlay() override;

	float CurrentThrottle = 0;
};
