// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.


#include "ValidationVolume.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Altar.h"
#include "EscapeRoomPlayerController.h"
#include "Engine/World.h"

AValidationVolume::AValidationVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	ValidationSphere = CreateDefaultSubobject<USphereComponent>("ValidationSphere");
	RootComponent = ValidationSphere;
}

void AValidationVolume::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap function
	ValidationSphere->OnComponentBeginOverlap.AddDynamic(this, &AValidationVolume::OnOverlapBegin);
}

void AValidationVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) 
{
	// Do nothing if the overlapping actor is not the player
	APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if(ER_PlayerCharacter == nullptr)
	{
		return;
	}

	// Call GameEnded on the PlayerController if the player is correct
	if(IsPlayerCorrect())
	{
		AEscapeRoomPlayerController* ER_PC = Cast<AEscapeRoomPlayerController>(GetWorld()->GetFirstPlayerController());
		if(ER_PC != nullptr)
		{
			ER_PC->GameEnded();
		}
		HandleEndGame();
	}
}

bool AValidationVolume::IsPlayerCorrect() 
{
	// Find all Altars actors in the world
	TArray<AActor*> Altars;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAltar::StaticClass(), Altars);

	// For each altar check if the player was right
	for(AActor* AltarActor : Altars)
	{
		AAltar* CastAltar = Cast<AAltar>(AltarActor);
		// false if on Altar is wrong
		if(!CastAltar->CheckValid())
		{
			return false;
		}
	}
	// true if all Altars are correct
	return true;
}
