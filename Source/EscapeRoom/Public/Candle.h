// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Candle.generated.h"

class UPointLightComponent;

/**
 *	Actor representing a light the player can turn on and off. 
 */
UCLASS()
class ESCAPEROOM_API ACandle : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	/** Actor mesh to be set in the editor */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	/** PointLight that can be turnd on and off */
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* FlameLight;

	/** Text to display if the player can reach the actor and the light if turned off */
	UPROPERTY(EditAnywhere)
	FText TurnOnText;

	/** Text to display if the player can reach the actor and the light if turned on */
	UPROPERTY(EditAnywhere)
	FText TurnOffText;
	
public:	
	ACandle();

	// Interact Interface overrides
	virtual FText GetInfoText() override;
	virtual void Interact(AActor* Caller) override;
};
