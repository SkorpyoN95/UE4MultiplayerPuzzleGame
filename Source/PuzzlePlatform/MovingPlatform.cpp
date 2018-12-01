// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (HasAuthority()) {
		FVector location = GetActorLocation();

		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float TravelledLength = (GetActorLocation() - GlobalStartLocation).Size();

		if (TravelledLength >= JourneyLength) {
			FVector temp = GlobalTargetLocation;
			GlobalTargetLocation = GlobalStartLocation;
			GlobalStartLocation = temp;
		}

		FVector direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		location += Speed * DeltaTime * direction;
		SetActorLocation(location);
	}
}
