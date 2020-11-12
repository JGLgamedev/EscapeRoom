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

UCLASS()
class ESCAPEROOM_API AArtifact : public AActor, public IInteractInterface, public IGrabInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY()
	APlayerCharacter* Grabber = nullptr;

	UPROPERTY(EditAnywhere)
	FText InfoText;

	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInstance*> Materials;

	int32 MaterialsIndex = 0;
	
public:	
	// Sets default values for this actor's properties
	AArtifact();

public:	
	class UStaticMesh* GetBaseMesh() const;
	class UMaterialInstance* GetMaterial() const;
	virtual FText GetInfoText() override;
	virtual void Interact(AActor* Caller) override;

	virtual void GrabItem(AActor* Caller) override;
	virtual void DropItem() override;
};
