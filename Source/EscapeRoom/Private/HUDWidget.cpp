// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"


FText UHUDWidget::GetInfoText() const
{
    return InfoText;
}

void UHUDWidget::SetInfoText(FText NewInfoText) 
{
    InfoText = NewInfoText;
}
