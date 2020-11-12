// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEROOM_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	FText GetInfoText() const;
	UFUNCTION(BlueprintPure)
	ESlateVisibility GetGrabTextVisibility() const;
	UFUNCTION(BlueprintPure)
	ESlateVisibility GetDropTextVisibility() const;
};
