// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"


// Sets default values
AInteractiveDoor::AInteractiveDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	RootComponent = DoorFrameMesh;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(DoorFrameMesh);
}

// Called when the game starts or when spawned
void AInteractiveDoor::BeginPlay()
{
	Super::BeginPlay();
	
	bDoorClosed = IsDoorClosed();
	SetupTimeLine();
}

// Called every frame
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
	FOnTimelineFloat TimelineCallback;
	FOnTimelineEventStatic TimelineFinishedCallback;

	if(CurveDoor != nullptr)
	{
		TimelineCallback.BindUFunction(this, FName{TEXT("TimelineCallback")});
        TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });

		DoorTimeline.AddInterpFloat(CurveDoor, TimelineCallback);
		DoorTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
		DoorTimeline.SetLooping(false);
	}
}
