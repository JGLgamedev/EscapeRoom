// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeRoomPlayerController.h"
#include "Blueprint/UserWidget.h"

void AEscapeRoomPlayerController::BeginPlay() 
{
    Super::BeginPlay();
    // Creates HUD and adds it to the viewport
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
    // Remove current FocusedWidget if it exists
    if(FocusWidget != nullptr)
    {
        FocusWidget->RemoveFromViewport();
        HUDWidget->AddToViewport();
    }
    // Add new widget to the screen 
    if(NewFocusWidget != nullptr)
    {
        HUDWidget->RemoveFromViewport();
        NewFocusWidget->AddToViewport();
    }
    FocusWidget = NewFocusWidget;
}

void AEscapeRoomPlayerController::GameEnded() 
{
    // Remove all widgets from screen
    if(HUDWidget != nullptr && HUDWidget->IsInViewport())
    {
        HUDWidget->RemoveFromViewport();
    }
    if(FocusWidget != nullptr && FocusWidget->IsInViewport())
    {
        FocusWidget->RemoveFromViewport();
    }
    // Create EndGame widget and add it to the screen
    if(EndGameClass != nullptr)
    {
        EndGameWidget = CreateWidget(this, EndGameClass);
        if(EndGameWidget != nullptr)
        {
            EndGameWidget->AddToViewport();
        }
    }
    // Disable Pawn input
    GetPawn()->DisableInput(this);
}
