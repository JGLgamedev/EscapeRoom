// Fill out your copyright notice in the Description page of Project Settings.


#include "Candle.h"
#include "Components/PointLightComponent.h"

// Sets default values
ACandle::ACandle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
	FlameLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Candle Light"));
	FlameLight->SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void ACandle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FText ACandle::GetInfoText() 
{
	if(FlameLight->IsVisible())
	{
		return TurnOffText;
	}
	else
	{
		return TurnOnText;
	}
}

void ACandle::Interact(AActor* Caller) 
{
	if(FlameLight->IsVisible())
	{
		FlameLight->SetVisibility(false);
	}
	else
	{
		FlameLight->SetVisibility(true);
	}
}

