// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.


#include "Artifact.h"
#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h" 
#include "Engine/StaticMesh.h" 
#include "Materials/MaterialInstance.h"

AArtifact::AArtifact()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	BaseMesh->SetSimulatePhysics(true);
}

void AArtifact::Interact(AActor* Caller) 
{
	if(Materials.Num() > 0)
	{
		// Change mesh material to one from the Materials array
		BaseMesh->SetMaterial(0, Materials[MaterialsIndex]);
		++MaterialsIndex;
		// MaterialsIndex must not be greater the Materials.Num() - 1
		MaterialsIndex %= Materials.Num();
	}
}

void AArtifact::GrabItem(AActor* Caller) 
{
	APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(Caller);
	// Can only grab if the Player is not already grabbing an actor.
	if(ER_PlayerCharacter && Grabber == nullptr)
	{
		// Deactivate physics and collision
		BaseMesh->SetSimulatePhysics(false);
		SetActorEnableCollision(false);
		// Attach the actor to the end of the Player's SpringArm
		AttachToComponent(ER_PlayerCharacter->GetSpringArm(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, USpringArmComponent::SocketName);
		Grabber = ER_PlayerCharacter;
	}
}

void AArtifact::DropItem() 
{
	// Can only drop if hold by a player
	if(Grabber != nullptr)
	{
		// Detach from SpringArm and activate physics and collision
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		BaseMesh->SetSimulatePhysics(true);
		SetActorEnableCollision(true);
		Grabber = nullptr;
	}
}
