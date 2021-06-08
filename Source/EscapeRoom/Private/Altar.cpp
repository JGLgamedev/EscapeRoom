// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.


#include "Altar.h"
#include "Components/BoxComponent.h" 
#include "Components/PointLightComponent.h"
#include "Artifact.h"

// Sets default values
AAltar::AAltar()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(RootComponent);
	ActivationLight = CreateDefaultSubobject<UPointLightComponent>("ActivationLight");
	ActivationLight->SetupAttachment(RootComponent);
}

void AAltar::BeginPlay() 
{
	Super::BeginPlay();

	// Bind overlap function
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAltar::OnTriggerBoxBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AAltar::OnTriggerBoxEndOverlap);
}

bool AAltar::CheckValid() const
{
	// Get all Artifacts inside TriggerBox
	TArray<AActor*> OverlappingActors;
	TriggerBox->GetOverlappingActors(OverlappingActors, AArtifact::StaticClass());
	// false if 0 or more than one Artifact is present
	if(OverlappingActors.Num() != 1)
	{
		return false;
	}
	// Compare CorrectMesh and CorrectMaterial to Artifact in TriggerBox.
	AArtifact* OverlappingArtifact = Cast<AArtifact>(OverlappingActors[0]);
	return ((OverlappingArtifact->GetBaseMesh() == CorrectMesh) && (OverlappingArtifact->GetMaterial() == CorrectMaterial));
}

void AAltar::OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	// Do nothing if the overlapping actor is not an artifact
	AArtifact* OverlappingArtifact = Cast<AArtifact>(OtherActor);
	if(OverlappingArtifact == nullptr)
	{
		return;
	}
	// Turn on the light if it is turned off
	if(!ActivationLight->IsVisible()) 
	{
		ActivationLight->SetVisibility(true);
	}
}

void AAltar::OnTriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	// Get all Artifacts inside TriggerBox
	TArray<AActor*> OverlappingActors;
	TriggerBox->GetOverlappingActors(OverlappingActors, AArtifact::StaticClass());
	// If there are no more overlapping actors, turn off the light
	if(OverlappingActors.Num() == 0 && ActivationLight->IsVisible())
	{
		ActivationLight->SetVisibility(false);
	}
}
