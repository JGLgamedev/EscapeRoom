// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/TimelineComponent.h"
#include "InteractiveDoor.generated.h"

class UCurveFloat;

UCLASS()
class ESCAPEROOM_API AInteractiveDoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorFrameMesh;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	FText OpenInfoText;

	UPROPERTY(EditAnywhere)
	FText CloseInfoText;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* CurveDoor;

	bool bDoorClosed = true;
	bool bDoorReady = true;

	UPROPERTY()
	FTimeline DoorTimeline;

public:	
	// Sets default values for this actor's properties
	AInteractiveDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FText GetInfoText() override;
	virtual void Interact(AActor* Caller) override;

	UFUNCTION()
    void TimelineCallback(float Value);

	UFUNCTION()
    void TimelineFinishedCallback();

private:
	bool IsDoorClosed();
	void SetupTimeLine();

};
