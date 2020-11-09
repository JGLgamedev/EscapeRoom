// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EscapeRoomPlayerController.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class ESCAPEROOM_API AEscapeRoomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget* HUD = nullptr;

	UPROPERTY()
	UUserWidget* FocusWidget = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	UUserWidget* GetHUD() const;
	void SetHUDInfoText(FText NewHUDInfoText);

	void SetFocusWidget(UUserWidget* NewFocusWidget);
	UUserWidget* GetFocusWidget() const;

};
