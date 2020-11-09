// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Candle.generated.h"

class UPointLightComponent;

UCLASS()
class ESCAPEROOM_API ACandle : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* FlameLight;

	UPROPERTY(EditAnywhere)
	FText TurnOnText;
	UPROPERTY(EditAnywhere)
	FText TurnOffText;
	
public:	
	// Sets default values for this actor's properties
	ACandle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FText GetInfoText() override;
	virtual void Interact(AActor* Caller) override;
};
