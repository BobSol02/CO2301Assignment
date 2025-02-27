// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "PC_PlayerController.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterMesh = GetMesh();
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->AttachToComponent(CharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("hand_rSocket")));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CharacterMesh);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	MapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Map Arm"));
	MapArm->SetupAttachment(CharacterMesh);
	MapArm->SetRelativeRotation(FRotator(-90.0f, 0, 0));
	MapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Map Camera"));
	MapCamera->SetupAttachment(MapArm);

	// If health not set in editor, set it to 100
	if (!Health)
		Health = 100;

	// If bullet damage not set in editor, set it to 20
	if (!BulletDamage)
		BulletDamage = 20;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::CallForwards);
	PlayerInputComponent->BindAxis("Strafe", this, &APlayerCharacter::CallStrafe);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::CallPitch);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::CallTurn);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::CallJump);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &APlayerCharacter::Shoot);
}

void APlayerCharacter::CallForwards(float Value) {
	this->AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerCharacter::CallStrafe(float Value) {
	this->AddMovementInput(GetActorRightVector(), Value);
}

void APlayerCharacter::CallPitch(float Value) {
	this->AddControllerPitchInput(Value);
}

void APlayerCharacter::CallTurn(float Value) {
	this->AddControllerYawInput(Value);
}

void APlayerCharacter::CallJump() {
	this->Jump();
}

void APlayerCharacter::Shoot() {
	AController* ControllerRef = GetController();
	if (ControllerRef->IsA(APC_PlayerController::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("player"));
		APC_PlayerController* playerController = (APC_PlayerController*)ControllerRef;
		int bullets = playerController->GetBullets();
		if (bullets > 0)
			playerController->SetBullets(bullets - 1);
		else
			return;
	}
	FVector CameraLocation;
	FRotator CameraRotation;
	ControllerRef->GetPlayerViewPoint(CameraLocation, CameraRotation);
	FVector end = CameraLocation + CameraRotation.Vector() * 10000.0f;
	FHitResult hit;
	bool hitSomething = GetWorld()->LineTraceSingleByChannel(hit, CameraLocation, end, ECC_Visibility);
	if (hitSomething) {
		if (hit.GetActor() != nullptr)
			if (hit.GetActor()->GetClass()->IsChildOf(APlayerCharacter::StaticClass())) {
				UE_LOG(LogTemp, Warning, TEXT("COOL"));
				UGameplayStatics::ApplyDamage(
					hit.GetActor(),
					BulletDamage,
					ControllerRef,
					this,
					UDamageType::StaticClass()
				);
			}
	}
}

/*
* TakeDamage function
* Applies damage to the character.
*/
float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser) {
	UE_LOG(LogTemp, Warning, TEXT("Instigator: %s, Causer: %s"), *EventInstigator->GetName(), *DamageCauser->GetName());
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("%d"), Health);
	if (Health <= 0)
		this->Destroy();
	return DamageAmount;
}

/*
* GetHealth function
* Called from blueprints. Returns player's health.
*/
int APlayerCharacter::GetHealth() {
	return Health;
}