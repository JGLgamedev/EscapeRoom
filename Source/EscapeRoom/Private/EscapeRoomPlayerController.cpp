// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeRoomPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacter.h"

void AEscapeRoomPlayerController::BeginPlay() 
{
    if(HUDClass != nullptr)
    {
        HUDWidget = CreateWidget(this, HUDClass);
        if(HUDWidget != nullptr)
        {
            HUDWidget->AddToViewport();
        }
    }
}

void AEscapeRoomPlayerController::SetFocusWidget(UUserWidget* NewFocusWidget) 
{
    if(FocusWidget != nullptr)
    {
        FocusWidget->RemoveFromViewport();
        HUDWidget->AddToViewport();
    }
    if(NewFocusWidget != nullptr)
    {
        HUDWidget->RemoveFromViewport();
        NewFocusWidget->AddToViewport();

    }
    FocusWidget = NewFocusWidget;
}

void AEscapeRoomPlayerController::GameEnded() 
{
    if(HUDWidget != nullptr && HUDWidget->IsInViewport())
    {
        HUDWidget->RemoveFromViewport();
    }
    if(FocusWidget != nullptr && FocusWidget->IsInViewport())
    {
        FocusWidget->RemoveFromViewport();
    }
    if(EndGameClass != nullptr)
    {
        EndGameWidget = CreateWidget(this, EndGameClass);
        if(EndGameWidget != nullptr)
        {
            EndGameWidget->AddToViewport();
        }
    }
    APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
    if(ER_PlayerCharacter != nullptr)
    {
        ER_PlayerCharacter->SetPlayerCanMove(false);
    }
}
