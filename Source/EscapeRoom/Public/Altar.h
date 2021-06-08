// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Altar.generated.h"

class UBoxComponent;
class UPointLightComponent;

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

	/** Light that turns on when the player puts an artifact into the altar*/
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* ActivationLight;

	/** Correct Artifact mesh the player has to put into the volume. To be set in the editor */
	UPROPERTY(EditAnywhere)
	UStaticMesh* CorrectMesh;

	/** Correct Artifact material the player has to put into the volume. To be set in the editor */
	UPROPERTY(EditAnywhere)
	UMaterialInstance* CorrectMaterial;

protected:
	virtual void BeginPlay() override;

public:	
	AAltar();

	/** Return true if CorrectMesh and CorrectMaterial match the Artifact placed in TriggerBox */
	bool CheckValid() const;

	/** Delegate functions called on trigger box overlap */
	UFUNCTION()
	void OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
