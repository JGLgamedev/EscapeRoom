// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ValidationVolume.generated.h"

class USphereComponent;
class USpotLightComponent;

UCLASS()
class ESCAPEROOM_API AValidationVolume : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* ValidationSphere;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USpotLightComponent* ValidationLight;

public:	
	// Sets default values for this actor's properties
	AValidationVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	bool IsPlayerCorrect();
};
