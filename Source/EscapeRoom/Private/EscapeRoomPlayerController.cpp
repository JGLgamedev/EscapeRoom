// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeRoomPlayerController.h"
#include "Blueprint/UserWidget.h"

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
