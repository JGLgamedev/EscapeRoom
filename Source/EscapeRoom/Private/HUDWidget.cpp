// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.


#include "HUDWidget.h"
#include "PlayerCharacter.h"
#include "InteractInterface.h"
#include "GrabInterface.h"

FText UHUDWidget::GetInfoText() const
{
    // Display InfoText from FocusedActor implementing InteractInterface if the player can interact with actors
    APlayerCharacter* ER_PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
    IInteractInterface* CanInteractActor = Cast<IInteractInterface>(ER_PlayerCharacter->GetFocusedActor());
    if(CanInteractActor != nullptr && ER_PlayerCharacter->GetPlayerCanInteract())
    {
        FText InfoText = CanInteractActor->GetInfoText();
        if(InfoText.IsEmpty())
        {
            return FText();
        }
        else if(!InfoText.IsEmpty() && InteractCommand.IsEmpty())
        {
            return InfoText;
        }
        else
        {
            return FText::Join(FText::FromString(TEXT(" : ")), InteractCommand, InfoText);
        }
    }
    else
    {
        return FText();
    }
}

ESlateVisibility UHUDWidget::GetGrabTextVisibility() const
{
    // Display Grab text if Player can grab FocusedActor
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
    // Display Drop text if Player can drop GrabbedActor
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
