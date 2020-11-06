// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "EscapeRoomPlayerController.h"
#include "HUDWidget.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	ReachInFront(HitResult);
	AActor* HitActor = HitResult.GetActor();

	if(HitActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT"));
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
}

void APlayerCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue) 
{
	AddControllerPitchInput(AxisValue);
}

void APlayerCharacter::LookRight(float AxisValue) 
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::ReachInFront(FHitResult& HitResult)
{
	FVector LineTraceStart;
	FRotator PlayerRotation;

	GetController()->GetPlayerViewPoint(LineTraceStart, PlayerRotation);
	FVector LineTraceEnd = LineTraceStart + PlayerRotation.Vector() * PlayerReach;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_Visibility);
}

void APlayerCharacter::SetHUDInfoText(FText NewInfoText) 
{
	AController* ControllerRef = GetController();
	if(ControllerRef != nullptr)
	{
		AEscapeRoomPlayerController* ERControllerRef = Cast<AEscapeRoomPlayerController>(ControllerRef);
		if(ERControllerRef != nullptr)
		{
			UUserWidget* UserWidgetRef = ERControllerRef->GetHUD();
			if(UserWidgetRef != nullptr)
			{
				UHUDWidget* HUDWidgetRef = Cast<UHUDWidget>(UserWidgetRef);
				if(HUDWidgetRef != nullptr)
				{
					HUDWidgetRef->SetInfoText(NewInfoText);
				}
			}
		}
	}
}
