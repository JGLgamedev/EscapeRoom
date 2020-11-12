// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "GrabInterface.h"
#include "Artifact.generated.h"

class APlayerCharacter;
class UStaticMesh;
class UMaterialInstance;

/**
 * Class representing an object the player has to put on the correct Altar.
 * Changes color when interacted with.
 * Can be picked up.
 */

UCLASS()
class ESCAPEROOM_API AArtifact : public AActor, public IInteractInterface, public IGrabInterface
{
	GENERATED_BODY()

	/** Actor mesh to be set in the editor */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	/** PlayerCharacter holding the actor. */
	UPROPERTY()
	APlayerCharacter* Grabber = nullptr;

	/** Text to display if the player can interact with the actor */
	UPROPERTY(EditAnywhere)
	FText InfoText;

	/** Array of materials the mesh can have. To be set in the editor */
	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> Materials;

	/** Index of the Materials array. */
	int32 MaterialsIndex = 0;
	
public:	
	AArtifact();

public:	
	// Accessors
	class UStaticMesh* GetBaseMesh() const { return BaseMesh->GetStaticMesh(); }
	class UMaterialInstance* GetMaterial() const { return Cast<UMaterialInstance>(BaseMesh->GetMaterial(0)); }
	// Interact Interface Overrides
	virtual FText GetInfoText() override { return InfoText; }
	virtual void Interact(AActor* Caller) override;
	// Grab Interface Overrides
	virtual void GrabItem(AActor* Caller) override;
	virtual void DropItem() override;
};
