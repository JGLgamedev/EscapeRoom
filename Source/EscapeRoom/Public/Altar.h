// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Altar.generated.h"

class UBoxComponent;

UCLASS()
class ESCAPEROOM_API AAltar : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere)
	UStaticMesh* CorrectMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* CorrectMaterial;

public:	
	// Sets default values for this actor's properties
	AAltar();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool CheckValid();

};
