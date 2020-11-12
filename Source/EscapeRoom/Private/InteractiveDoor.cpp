// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"


AInteractiveDoor::AInteractiveDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	RootComponent = DoorFrameMesh;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(DoorFrameMesh);
}

void AInteractiveDoor::BeginPlay()
{
	Super::BeginPlay();
	
	bDoorClosed = IsDoorClosed();
	SetupTimeLine();
}

void AInteractiveDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorTimeline.TickTimeline(DeltaTime);
}

FText AInteractiveDoor::GetInfoText() 
{
	if(!bDoorReady)
	{
		return FText();
	}
	if(bDoorClosed)
	{
		return OpenInfoText;
	}
	else
	{
		return CloseInfoText;
	}
	
}

void AInteractiveDoor::Interact(AActor* Caller) 
{
	// Animate door depending on state
	if(bDoorReady)
	{
		bDoorReady = false;
		if(bDoorClosed)
		{
			DoorTimeline.PlayFromStart();
		}
		else
		{
			DoorTimeline.ReverseFromEnd();
		}
	}
}

void AInteractiveDoor::TimelineCallback(float Value) 
{
	// Set door relative rotation depending on the timeline value
	float NewYaw = FMath::Lerp(0.f, 90.f, Value);
	FRotator DoorMeshRot = DoorMesh->GetRelativeRotation();
	DoorMesh->SetRelativeRotation(FRotator(
		DoorMeshRot.Pitch,
		NewYaw,
		DoorMeshRot.Roll
	));
}

void AInteractiveDoor::TimelineFinishedCallback() 
{
	bDoorClosed = !bDoorClosed;
	bDoorReady = true;
}

bool AInteractiveDoor::IsDoorClosed() 
{
	// Door is considered closed if its relative yaw = 0.f
	if(DoorMesh->GetRelativeRotation().Yaw == 0.f){
		return true;
	}
	else
	{
		return false;
	}
}

void AInteractiveDoor::SetupTimeLine() 
{
	// Delegates
	FOnTimelineFloat TimelineCallback;
	FOnTimelineEventStatic TimelineFinishedCallback;

	if(CurveDoor != nullptr)
	{
		// Bind callback functions to delegates
		TimelineCallback.BindUFunction(this, FName{TEXT("TimelineCallback")});
        TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		DoorTimeline.AddInterpFloat(CurveDoor, TimelineCallback);
		DoorTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
		// Timeline does not loop
		DoorTimeline.SetLooping(false);
	}
}
