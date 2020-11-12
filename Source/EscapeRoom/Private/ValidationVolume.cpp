// Fill out your copyright notice in the Description page of Project Settings.


#include "ValidationVolume.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Altar.h"
#include "EscapeRoomPlayerController.h"
#include "Engine/World.h"

// Sets default values
AValidationVolume::AValidationVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ValidationSphere = CreateDefaultSubobject<USphereComponent>("ValidationSphere");
	RootComponent = ValidationSphere;
	ValidationLight = CreateDefaultSubobject<USpotLightComponent>("ValidationLight");
	ValidationLight->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AValidationVolume::BeginPlay()
{
	Super::BeginPlay();
	
	ValidationSphere->OnComponentBeginOverlap.AddDynamic(this, &AValidationVolume::OnOverlapBegin);
}

void AValidationVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) 
{
	APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if(ER_PlayerCharacter == nullptr)
	{
		return;
	}

	if(IsPlayerCorrect())
	{
		AEscapeRoomPlayerController* ER_PC = Cast<AEscapeRoomPlayerController>(GetWorld()->GetFirstPlayerController());
		if(ER_PC != nullptr)
		{
			ER_PC->GameEnded();
		}
	}
}

bool AValidationVolume::IsPlayerCorrect() 
{
	TArray<AActor*> Altars;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAltar::StaticClass(), Altars);

	for(AActor* AltarActor : Altars)
	{
		AAltar* CastAltar = Cast<AAltar>(AltarActor);
		if(!CastAltar->CheckValid())
		{
			return false;
		}
	}
	return true;
}
