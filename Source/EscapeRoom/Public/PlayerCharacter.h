// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AEscapeRoomPlayerController;

/**
 * Main Player Character class.
 * Can move, grab and interact with actors
 */
UCLASS()
class ESCAPEROOM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Player camera */
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamera;

	/** Spring arm to attach grabbed objects to */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	/** How far the player can reach */
	UPROPERTY(EditAnywhere)
	float PlayerReach = 100.f;

	/** Actor the player is looking at */
	UPROPERTY()
	AActor* FocusedActor = nullptr;

	/** Actor the player is grabbing */
	UPROPERTY()
	AActor* GrabbedActor = nullptr;

	/** Player state */
	bool bPlayerCanMove = true;
	bool bPlayerCanInteract = true;

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input bindings
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void Interact();
	void CancelFocus();
	void Grab();
	void QuitGame();

	// Line trace in front a the Player. Called every frame.
	bool ReachInFront(FHitResult& HitResult);

	// Accessors
	bool GetPlayerCanMove() const { return bPlayerCanMove; }
	void SetPlayerCanMove(bool bNewPlayerCanMove) { bPlayerCanMove = bNewPlayerCanMove; }
	bool GetPlayerCanInteract() const { return bPlayerCanInteract; }
	void SetPlayerCanInteract(bool bNewPlayerCanInteract) { bPlayerCanInteract = bNewPlayerCanInteract; }
	USpringArmComponent* GetSpringArm() const { return SpringArm; }
	AActor* GetFocusedActor() const { return FocusedActor; }
	AActor* GetGrabbedActor() const { return GrabbedActor; }
};
