// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// we want all the towers rotating towards the enemy continously all the time 

	if (Tank)
	{
		float DistanceToTank = FVector::Dist(Tank->GetActorLocation(),GetActorLocation());
		if (DistanceToTank <= FireRange)
		{
		RotateTurret(Tank->GetActorLocation());
		}

	}

}
