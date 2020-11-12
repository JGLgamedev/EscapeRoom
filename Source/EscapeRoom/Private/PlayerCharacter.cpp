// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h" 
#include "EscapeRoomPlayerController.h"
#include "InteractInterface.h"
#include "GrabInterface.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->bUsePawnControlRotation = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(PlayerCamera);
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
	FocusedActor = HitResult.GetActor();
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
	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &APlayerCharacter::Grab);
	PlayerInputComponent->BindAction("Quit", IE_Pressed, this, &APlayerCharacter::QuitGame);
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
	if(bPlayerCanInteract && FocusedActor != nullptr)
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
	AEscapeRoomPlayerController* ER_PlayerControllerRef = Cast<AEscapeRoomPlayerController>(GetController());
	if(ER_PlayerControllerRef != nullptr)
	{
		ER_PlayerControllerRef->SetFocusWidget(nullptr);
	}
	bPlayerCanMove = true;
	bPlayerCanInteract = true;
}

void APlayerCharacter::Grab() 
{
	if(GrabbedActor == nullptr && FocusedActor != nullptr)
	{
		IGrabInterface* GrabActor = Cast<IGrabInterface>(FocusedActor);
		if(GrabActor != nullptr)
		{
			GrabActor->GrabItem(this);
			GrabbedActor = FocusedActor;
		}
	}
	else
	{
		IGrabInterface* GrabActor = Cast<IGrabInterface>(GrabbedActor);
		if(GrabActor != nullptr)
		{
			GrabActor->DropItem();
			GrabbedActor = nullptr;
		}
	}
}
void APlayerCharacter::QuitGame()
{
	// Quit the game using a console command
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController)
	{
		PlayerController->ConsoleCommand("quit");
	}
}

bool APlayerCharacter::ReachInFront(FHitResult& HitResult)
{
	FVector LineTraceStart;
	FRotator PlayerRotation;

	GetController()->GetPlayerViewPoint(LineTraceStart, PlayerRotation);
	FVector LineTraceEnd = LineTraceStart + PlayerRotation.Vector() * PlayerReach;
	
	return GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_Visibility);
}
