// Fill out your copyright notice in the Description page of Project Settings.


#include "Altar.h"
#include "Components/BoxComponent.h" 
#include "Artifact.h"

// Sets default values
AAltar::AAltar()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(RootComponent);
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
