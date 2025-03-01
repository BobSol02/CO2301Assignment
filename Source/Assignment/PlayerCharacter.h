// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Grenade.h"
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

	// Components
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* CharacterMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* GunMesh;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* MapArm;
	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* MapCamera;
	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGrenade> GrenadeClass;

	//Bindings
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
	UFUNCTION()
	virtual void ThrowGrenade();
public:
	//Declared public so that it can be accessed by BT_Fire task
	UFUNCTION()
	virtual void Shoot();
protected:
	// Variables
	UPROPERTY(EditAnywhere)
	int BulletDamage = 0;
	UPROPERTY(EditAnywhere)
	int Health = 0;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	int GetHealth();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
