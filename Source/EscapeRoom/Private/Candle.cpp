// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.


#include "Candle.h"
#include "Components/PointLightComponent.h"

ACandle::ACandle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
	FlameLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Candle Light"));
	FlameLight->SetupAttachment(BaseMesh);

}

FText ACandle::GetInfoText() 
{
	return (FlameLight->IsVisible()) ? TurnOffText : TurnOnText;
}

void ACandle::Interact(AActor* Caller) 
{
	(FlameLight->IsVisible()) ? FlameLight->SetVisibility(false) :FlameLight->SetVisibility(true);
}

