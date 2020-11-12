// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact.h"
#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h" 

#include "Engine/StaticMesh.h" 
#include "Materials/MaterialInstance.h"

// Sets default values
AArtifact::AArtifact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	BaseMesh->SetSimulatePhysics(true);
}

UStaticMesh* AArtifact::GetBaseMesh() const
{
	return BaseMesh->GetStaticMesh();
}

UMaterialInstance* AArtifact::GetMaterial() const
{
	return Cast<UMaterialInstance>(BaseMesh->GetMaterial(0));
}

FText AArtifact::GetInfoText() 
{
	return InfoText;
}

void AArtifact::Interact(AActor* Caller) 
{
	if(Materials.Num() > 0)
	{
		BaseMesh->SetMaterial(0, Materials[MaterialsIndex]);
		++MaterialsIndex;
		MaterialsIndex %= Materials.Num();
	}
}

void AArtifact::GrabItem(AActor* Caller) 
{
	APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(Caller);
	if(ER_PlayerCharacter && Grabber == nullptr)
	{
		BaseMesh->SetSimulatePhysics(false);
		SetActorEnableCollision(false);
		AttachToComponent(ER_PlayerCharacter->GetSpringArm(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, USpringArmComponent::SocketName);
		ER_PlayerCharacter->SetPlayerCanInteract(false);
		Grabber = ER_PlayerCharacter;
	}
}

void AArtifact::DropItem() 
{
	if(Grabber != nullptr)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		BaseMesh->SetSimulatePhysics(true);
		SetActorEnableCollision(true);
		Grabber->SetPlayerCanInteract(true);
		Grabber = nullptr;
	}
}
