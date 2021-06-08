// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ValidationVolume.generated.h"

class USphereComponent;

/**
 * Actor representing a volume the Player has to step into to validate his guess.
 * Represented by a light in the world.
 */
UCLASS()
class ESCAPEROOM_API AValidationVolume : public AActor
{
	GENERATED_BODY()

	/** Actor mesh to be set in the editor */
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* ValidationSphere;

public:	
	AValidationVolume();

protected:
	virtual void BeginPlay() override;

public:
	// Delegate function called on sphere overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void HandleEndGame();


private:
	// Calls all Altars in the scene to check player's guess
	bool IsPlayerCorrect();
};
