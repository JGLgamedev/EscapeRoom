// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * Main HUD class.
 * Get HUD information from PlayerCharacter.
 */
UCLASS()
class ESCAPEROOM_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	/** Command to display if the player can interact with something */
	UPROPERTY(EditAnywhere)
	FText InteractCommand;

public:

	UFUNCTION(BlueprintPure)
	FText GetInfoText() const;
	UFUNCTION(BlueprintPure)
	ESlateVisibility GetGrabTextVisibility() const;
	UFUNCTION(BlueprintPure)
	ESlateVisibility GetDropTextVisibility() const;
};
