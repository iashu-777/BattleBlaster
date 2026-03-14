// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle,this,&ATower::CheckFireCondition,FireRate,true);
}

bool ATower::IsInFireRange()
{
	if (Tank)
	{
		float DistanceToTank = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
		if (DistanceToTank <= FireRange)
		{
			return true;
		}
	}
	return false;
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// we want all the towers rotating towards the enemy continously all the time 

	if (IsInFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}

}

void ATower::CheckFireCondition()
{
	UE_LOG(LogTemp, Display, TEXT("Timeout!"));

	if (Tank && Tank->IsAlive &&IsInFireRange())
	{
		Fire();
	}
}


void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
	UE_LOG(LogTemp, Display, TEXT("Tower Handle destruction"));
}


