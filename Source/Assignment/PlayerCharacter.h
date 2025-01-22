// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ASSIGNMENT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* CharacterMesh;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UFUNCTION()
	virtual void CallForwards(float Value);
	UFUNCTION()
	virtual void CallStrafe(float Value);
	UFUNCTION()
	virtual void CallPitch(float Value);
	UFUNCTION()
	virtual void CallTurn(float Value);
	UFUNCTION()
	virtual void CallJump();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
