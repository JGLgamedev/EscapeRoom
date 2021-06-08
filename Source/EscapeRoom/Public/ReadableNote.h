// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "ReadableNote.generated.h"

class UUserWidget;
class AEscapeRoomPlayerController;

/**
 * Actor representing an object that the player can read.
 * Implements InteractInterface.
 * Display a widget to the screen when interacted with.
 */

UCLASS()
class ESCAPEROOM_API AReadableNote : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	/** Actor mesh to be set in the editor */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	/** Widget to be dispalyed, to be set in the editor */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> NoteWidgetClass;

	/** Info text for UI, to be set in the editor */
	UPROPERTY(EditAnywhere)
	FText InfoText;

	/** Widget instance created during BeginPlay */
	UPROPERTY()
	UUserWidget* NoteWidget;

	/** PlayerController reference to add the widget to the screen */
	UPROPERTY()
	AEscapeRoomPlayerController* ER_PlayerControllerRef = nullptr;

public:	
	AReadableNote();

protected:
	virtual void BeginPlay() override;

public:	
	// InteractInterface overrides
	virtual FText GetInfoText() override;
	virtual void Interact(AActor* Caller) override;
};
