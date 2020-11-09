// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "EscapeRoomPlayerController.h"
#include "InteractInterface.h"

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

	ER_PlayerControllerRef = Cast<AEscapeRoomPlayerController>(GetController());

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	bool bHit = ReachInFront(HitResult);

	FocusedActor = HitResult.GetActor();

	IInteractInterface* InteractActor = Cast<IInteractInterface>(FocusedActor);
	if(InteractActor != nullptr)
	{
		SetHUDInfoText(InteractActor->GetInfoText());
	}
	else
	{
		SetHUDInfoText(FText());
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
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Cancel", IE_Pressed, this, &APlayerCharacter::CancelFocus);
}

void APlayerCharacter::MoveForward(float AxisValue) 
{
	if(bPlayerCanMove)
	{
		AddMovementInput(GetActorForwardVector(), AxisValue);
	}
}

void APlayerCharacter::MoveRight(float AxisValue) 
{
	if(bPlayerCanMove)
	{
		AddMovementInput(GetActorRightVector(), AxisValue);
	}
}

void APlayerCharacter::LookUp(float AxisValue) 
{
	if(bPlayerCanMove)
	{
		AddControllerPitchInput(AxisValue);
	}
}

void APlayerCharacter::LookRight(float AxisValue) 
{
	if(bPlayerCanMove)
	{
		AddControllerYawInput(AxisValue);
	}
}

void APlayerCharacter::Interact() 
{
	if(bPlayerCanMove && FocusedActor != nullptr)
	{
		IInteractInterface* InteractActor = Cast<IInteractInterface>(FocusedActor);
		if(InteractActor != nullptr)
		{
			InteractActor->Interact(this);
		}
	}
}

void APlayerCharacter::CancelFocus() 
{
	if(ER_PlayerControllerRef != nullptr)
	{
		if(ER_PlayerControllerRef->GetFocusWidget() != nullptr)
		{
			ER_PlayerControllerRef->SetFocusWidget(nullptr);
		}
	}
	bPlayerCanMove = true;
}

bool APlayerCharacter::ReachInFront(FHitResult& HitResult)
{
	FVector LineTraceStart;
	FRotator PlayerRotation;

	GetController()->GetPlayerViewPoint(LineTraceStart, PlayerRotation);
	FVector LineTraceEnd = LineTraceStart + PlayerRotation.Vector() * PlayerReach;
	
	return GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_Visibility);
}

void APlayerCharacter::SetHUDInfoText(FText NewInfoText) 
{
	if(ER_PlayerControllerRef != nullptr)
	{
		ER_PlayerControllerRef->SetHUDInfoText(NewInfoText);
	}
}

bool APlayerCharacter::GetPlayerCanMove() 
{
	return bPlayerCanMove;
}

void APlayerCharacter::SetPlayerCanMove(bool bNewPlayerCanMove) 
{
	bPlayerCanMove = bNewPlayerCanMove;
}
