// Fill out your copyright notice in the Description page of Project Settings.


#include "Altar.h"
#include "Components/BoxComponent.h" 
#include "Artifact.h"

// Sets default values
AAltar::AAltar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(RootComponent);
}

void AAltar::Tick(float DeltaTime) 
{
	
}

bool AAltar::CheckValid() 
{
	TArray<AActor*> OverlappingActors;
	TriggerBox->GetOverlappingActors(OverlappingActors, AArtifact::StaticClass());
	if(OverlappingActors.Num() != 1)
	{
		return false;
	}
	AArtifact* OverlappingArtifact = Cast<AArtifact>(OverlappingActors[0]);
	return ((OverlappingArtifact->GetBaseMesh() == CorrectMesh) && (OverlappingArtifact->GetMaterial() == CorrectMaterial));
}
