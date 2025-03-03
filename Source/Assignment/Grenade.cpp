// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GrenadeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Grenade Mesh"));
	GrenadeMesh->SetupAttachment(RootComponent);
	GrenadeMesh->SetSimulatePhysics(true);
	GrenadeMesh->SetNotifyRigidBodyCollision(true);
	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force"));
	RadialForce->SetupAttachment(GrenadeMesh);
	//ExplosionParticleSystem = CreateDefaultSubobject<UNiagaraSystem>(TEXT("Explosion Particle System"));
	//ExplosionParticleSystem->SetupAttachment(GrenadeMesh);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	// If movement speed not set in editor, set to 1000.0f
	ProjectileMovement->MaxSpeed = (MovementSpeed) ? MovementSpeed : 1000.0f;
	ProjectileMovement->InitialSpeed = ProjectileMovement->MaxSpeed;
	// Make grenade bounce
	ProjectileMovement->bShouldBounce = true;
	// If grenade damage not set in editor, set to 100.0f
	GrenadeDamage = (GrenadeDamage) ? GrenadeDamage : 100.0f;
	// If impulse radius not set in editor, set to 100.0f
	ImpulseRadius = (ImpulseRadius) ? ImpulseRadius : 100.0f;
	// If impulse strength not set in editor, set to 100.0f
	RadialForce->ForceStrength = (ImpulseStrength) ? ImpulseStrength : 500.0f;
	// If game duration not set in editor, set it to 2.0f
	if (!ExplosionTimer)
		ExplosionTimer = 2.0f;
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AGrenade::Explosion, ExplosionTimer, false);
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
* Explosion function
* Handles explosion after timer passes
*/
void AGrenade::Explosion() {
	UNiagaraComponent* ExplosionSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ExplosionParticleSystem,
		this->GetActorLocation(),
		this->GetActorRotation(),
		this->GetActorScale(),
		true,
		true,
		ENCPoolMethod::AutoRelease,
		true
	);
	// This is possible from the editor by going into the emitter state and changing the loop behaviour to once.
	// For some weird reason this would not save and this would lead to explosion animation never stoping.
	// The following code disables the system manually after it executes once.
	GetWorld()->GetTimerManager().SetTimer(Timer, [ExplosionSystem]() { ExplosionSystem->Deactivate(); }, 2.35f, false);
	RadialForce->FireImpulse();
	//https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Kismet/UGameplayStatics/ApplyRadialDamage?application_version=5.5
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		GrenadeDamage,
		this->GetActorLocation(),
		ImpulseRadius,
		UDamageType::StaticClass(),
		TArray<AActor*>(),
		this,
		this->GetInstigatorController(),
		false // Damage should scale
	);
	this->Destroy();
}