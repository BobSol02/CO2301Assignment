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
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	// If movement speed not set in editor, set to 1000.0f
	ProjectileMovement->MaxSpeed = (MovementSpeed) ? MovementSpeed : 1000.0f;
	ProjectileMovement->InitialSpeed = ProjectileMovement->MaxSpeed;
	// If grenade damage not set in editor, set to 100.0f
	GrenadeDamage = (GrenadeDamage) ? GrenadeDamage : 100.0f;
	// TODO: change
	InitialLifeSpan = 10.0f;
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AGrenade::OnHit);
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenade::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass())) {
		AActor* ProjectileOwner = GetOwner();
		if (ProjectileOwner == nullptr)
			return;
		UGameplayStatics::ApplyDamage(
			OtherActor, //actor that will be damaged
			GrenadeDamage, //the base damage to apply
			ProjectileOwner->GetInstigatorController(), //controller that caused the damage
			this, //Actor that actually caused the damage
			UDamageType::StaticClass() //class that describes the damage that was done
		);
		Destroy();
	}
}