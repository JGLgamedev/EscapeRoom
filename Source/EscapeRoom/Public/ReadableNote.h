// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "ReadableNote.generated.h"

class UUserWidget;
class AEscapeRoomPlayerController;

UCLASS()
class ESCAPEROOM_API AReadableNote : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> NoteWidgetClass;

	UPROPERTY(EditAnywhere)
	FText InfoText;

	UPROPERTY()
	UUserWidget* NoteWidget;

	UPROPERTY()
	AEscapeRoomPlayerController* ER_PlayerControllerRef = nullptr;

public:	
	// Sets default values for this actor's properties
	AReadableNote();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FText GetInfoText() override;
	virtual void Interact(AActor* Caller) override;
};
