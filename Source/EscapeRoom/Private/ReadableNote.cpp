// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadableNote.h"
#include "Blueprint/UserWidget.h"
#include "EscapeRoomPlayerController.h"
#include "PlayerCharacter.h"

// Sets default values
AReadableNote::AReadableNote()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void AReadableNote::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerControllerRef = GetWorld()->GetFirstPlayerController();
	if(PlayerControllerRef != nullptr){
		ER_PlayerControllerRef = Cast<AEscapeRoomPlayerController>(PlayerControllerRef);

		if(NoteWidgetClass != nullptr)
		{
			NoteWidget = CreateWidget(PlayerControllerRef, NoteWidgetClass);
		}
	}
}

// Called every frame
void AReadableNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FText AReadableNote::GetInfoText() 
{
	return InfoText;
}

void AReadableNote::Interact(AActor* Caller) 
{
	// Display Widget
	if(ER_PlayerControllerRef != nullptr)
	{
		ER_PlayerControllerRef->SetFocusWidget(NoteWidget);
	}
	// Lock Player in place
	if(Caller != nullptr)
	{
		APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(Caller);
		if(ER_PlayerCharacter != nullptr)
		{
			ER_PlayerCharacter->SetPlayerCanMove(false);
			ER_PlayerCharacter->SetPlayerCanInteract(false);
		}
	}
}
