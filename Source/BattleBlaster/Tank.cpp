// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"

ATank::ATank()
{
	SpringArmComp=CreateDefaultSubobject<USpringArmComponent>(TEXT("SprinArmComp"));
	SpringArmComp->SetupAttachment(CapsuleComp);

	CameraComp=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		}
	}
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		FVector ImpactPoint=HitResult.ImpactPoint;
		DrawDebugSphere(GetWorld(), ImpactPoint, 10.0f, 32, FColor::Blue);
		RotateTurret(ImpactPoint);
	}


}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
		EIC->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::TurnInput);
		EIC->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);


	}
}

void ATank::MoveInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();

	FVector DeltaLocation = FVector(0.0f,0.0f,0.0f);
	DeltaLocation.X = (Speed * InputValue) * GetWorld()->GetDeltaSeconds();

	 
	AddActorLocalOffset(DeltaLocation, true);//it adds location offest of an actor
	//UE_LOG(LogTemp, Display, TEXT("Input Value = %f"),InputValue);
}

void ATank::TurnInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();

	FRotator DeltaRotation = FRotator(0.0f,0.0f,0.0f);
	DeltaRotation.Yaw = (TurnRate * InputValue) * GetWorld()->GetDeltaSeconds(); //yaw to turn around Z

	AddActorLocalRotation(DeltaRotation, true); // it makes actor rotate using a local space rotation

}


void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	UE_LOG(LogTemp, Display, TEXT("Tank Handle destruction"));
}
