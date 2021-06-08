// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/TimelineComponent.h"
#include "InteractiveDoor.generated.h"

class UCurveFloat;

/**
 * Actor representing a door that can be opened and closed.
 * Has a DoorFrame mesh and a Door mesh.
 * Door rotates relatives to the frame.
 * Uses a Timeline and a CurveFloat.
 * Implements InteractInterface.
 */
UCLASS()
class ESCAPEROOM_API AInteractiveDoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	/** Door frame mesh to be set in the editor */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorFrameMesh;
	
	/** Door mesh to be set in the editor */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	/** Text to display when door is closed. */
	UPROPERTY(EditAnywhere)
	FText OpenInfoText;

	/** Text to display when door is open. */
	UPROPERTY(EditAnywhere)
	FText CloseInfoText;

	/** CurveFloat used to determine door position */
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* CurveDoor;

	/** Boolean to determine door state */
	bool bDoorClosed = true;
	bool bDoorReady = true;

	/** Timeline used to animate door */
	UPROPERTY()
	FTimeline DoorTimeline;

public:	
	AInteractiveDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// InteractInterface overrides
	virtual FText GetInfoText() override;
	virtual void Interact(AActor* Caller) override;

	// Timeline callbacks
	/** Function called when the timeline ticks */
	UFUNCTION()
    void TimelineCallback(float Value);
	/** Function called when the timeline ends */
	UFUNCTION()
    void TimelineFinishedCallback();

private:
	bool IsDoorClosed();
	void SetupTimeLine();
};
