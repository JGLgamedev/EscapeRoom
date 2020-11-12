// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Altar.generated.h"

class UBoxComponent;

/**
 * Altar where the player has to drop an Artifact into.
 * Correct Mesh and Material to be set in editor.
 * Can be called to check if player guess if valid.
 */

UCLASS()
class ESCAPEROOM_API AAltar : public AActor
{
	GENERATED_BODY()
	
	/** Altar mesh to be set in the editor */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	/** Volume where the player has to drop an Artifact into */
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	/** Correct Artifact mesh the player has to put into the volume. To be set in the editor */
	UPROPERTY(EditAnywhere)
	UStaticMesh* CorrectMesh;

	/** Correct Artifact material the player has to put into the volume. To be set in the editor */
	UPROPERTY(EditAnywhere)
	UMaterialInstance* CorrectMaterial;

public:	
	AAltar();

	/** Return true if CorrectMesh and CorrectMaterial match the Artifact placed in TriggerBox */
	bool CheckValid() const;

};
