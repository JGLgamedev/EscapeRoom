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
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> EndGameClass;

	UPROPERTY()
	UUserWidget* HUDWidget = nullptr;
	UPROPERTY()
	UUserWidget* EndGameWidget = nullptr;
	UPROPERTY()
	UUserWidget* FocusWidget = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	void SetFocusWidget(UUserWidget* NewFocusWidget);
	void GameEnded();

	UUserWidget* GetHUDWidget() const { return HUDWidget; };
	UUserWidget* GetFocusWidget() const { return FocusWidget; };

};
