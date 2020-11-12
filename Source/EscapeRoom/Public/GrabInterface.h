// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GrabInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGrabInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ESCAPEROOM_API IGrabInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GrabItem(AActor* Caller) =0;
	virtual void DropItem() =0;

};
