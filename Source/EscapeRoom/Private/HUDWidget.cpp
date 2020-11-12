// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "PlayerCharacter.h"
#include "InteractInterface.h"
#include "GrabInterface.h"

FText UHUDWidget::GetInfoText() const
{
    APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
    IInteractInterface* CanInteractActor = Cast<IInteractInterface>(ER_PlayerCharacter->GetFocusedActor());

    if(CanInteractActor != nullptr && ER_PlayerCharacter->GetPlayerCanInteract())
    {
        return CanInteractActor->GetInfoText();
    }
    else
    {
        return FText();
    }
}

ESlateVisibility UHUDWidget::GetGrabTextVisibility() const
{
    APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
    IGrabInterface* CanGrabActor = Cast<IGrabInterface>(ER_PlayerCharacter->GetFocusedActor());

    if(ER_PlayerCharacter->GetGrabbedActor() == nullptr && CanGrabActor != nullptr)
    {
        return ESlateVisibility::Visible;
    }
    else
    {
        return ESlateVisibility::Collapsed;
    }
}

ESlateVisibility UHUDWidget::GetDropTextVisibility() const
{
    APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
    
    if(ER_PlayerCharacter->GetGrabbedActor() != nullptr)
    {
        return ESlateVisibility::Visible;
    }
    else
    {
        return ESlateVisibility::Collapsed;
    }
}
