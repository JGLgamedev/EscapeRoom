// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeRoomPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.h"

void AEscapeRoomPlayerController::BeginPlay() 
{
    if(HUDClass != nullptr)
    {
        HUD = CreateWidget(this, HUDClass);
        if(HUD != nullptr)
        {
            HUD->AddToViewport();
        }
    }
}

UUserWidget* AEscapeRoomPlayerController::GetHUD() const
{
    return HUD;
}

void AEscapeRoomPlayerController::SetHUDInfoText(FText NewHUDInfoText) 
{
    if(HUD != nullptr)
    {
        UHUDWidget* HUDWidget = Cast<UHUDWidget>(HUD);
        if(HUDWidget != nullptr)
        {
            HUDWidget->SetInfoText(NewHUDInfoText);
        }
    }
}

void AEscapeRoomPlayerController::SetFocusWidget(UUserWidget* NewFocusWidget) 
{
    if(FocusWidget != nullptr)
    {
        FocusWidget->RemoveFromParent();
        HUD->AddToViewport();
    }
    if(NewFocusWidget != nullptr)
    {
        HUD->RemoveFromParent();
        NewFocusWidget->AddToViewport();

    }
    FocusWidget = NewFocusWidget;
}

UUserWidget* AEscapeRoomPlayerController::GetFocusWidget() const
{
    return FocusWidget;
}
