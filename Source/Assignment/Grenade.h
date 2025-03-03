// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Grenade.generated.h"

UCLASS()
class ASSIGNMENT_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GrenadeMesh;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForce;
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ExplosionParticleSystem;
	UPROPERTY()
	FTimerHandle Timer;
	UPROPERTY(EditAnywhere)
	float ExplosionTimer = 0;
	UFUNCTION()
	void Explosion();
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 0;
	UPROPERTY(EditAnywhere)
	float GrenadeDamage = 0;
	UPROPERTY(EditAnywhere)
	float ImpulseRadius = 0;
	UPROPERTY(EditAnywhere)
	float ImpulseStrength = 0;
};
