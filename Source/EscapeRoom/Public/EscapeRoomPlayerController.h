// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EscapeRoomPlayerController.generated.h"

class UUserWidget;

/**
 * Main PlayerController for the game.
 * Handles HUD and ends the game.
 */
UCLASS()
class ESCAPEROOM_API AEscapeRoomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	/** HUD widget class to be set in the editor */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDClass;

	/** End game widget class to be set in the editor */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> EndGameClass;

	/** HUDWidget instance */
	UPROPERTY()
	UUserWidget* HUDWidget = nullptr;

	/** EndGameWidget instance */
	UPROPERTY()
	UUserWidget* EndGameWidget = nullptr;

	/** Widget instance added to the screen by another actor */
	UPROPERTY()
	UUserWidget* FocusWidget = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	/** Adds a new widget to the screen and removes HUD */
	void SetFocusWidget(UUserWidget* NewFocusWidget);
	/** Handles ending screen */
	void GameEnded();

	// Accessors
	UUserWidget* GetHUDWidget() const { return HUDWidget; };
	UUserWidget* GetFocusWidget() const { return FocusWidget; };

};
