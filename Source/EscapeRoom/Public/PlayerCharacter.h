// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AEscapeRoomPlayerController;

UCLASS()
class ESCAPEROOM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float PlayerReach = 100.f;

	UPROPERTY()
	AActor* FocusedActor = nullptr;

	UPROPERTY()
	AEscapeRoomPlayerController* ER_PlayerControllerRef = nullptr;

	bool bPlayerCanMove = true;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void Interact();
	void CancelFocus();

	bool ReachInFront(FHitResult& HitResult);
	void SetHUDInfoText(FText NewInfoText);
	bool GetPlayerCanMove();
	void SetPlayerCanMove(bool bNewPlayerCanMove);

};
