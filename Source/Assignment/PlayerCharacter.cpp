// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "PC_PlayerController.h"
#include "AssignmentGameModeBase.h"

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
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(CharacterMesh);

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
	PlayerInputComponent->BindAction("ThrowGrenade", EInputEvent::IE_Pressed, this, &APlayerCharacter::ThrowGrenade);
}

/*
* CallForwards function
* Moves character in the x direction relative to the character.
*/
void APlayerCharacter::CallForwards(float Value) {
	this->AddMovementInput(GetActorForwardVector(), Value);
}

/*
* CallStrafe function
* Moves character in the y direction relative to the character.
*/
void APlayerCharacter::CallStrafe(float Value) {
	this->AddMovementInput(GetActorRightVector(), Value);
}

/*
* CallPitch function
* Rotates camera up/down.
*/
void APlayerCharacter::CallPitch(float Value) {
	this->AddControllerPitchInput(Value);
}

/*
* CallTurn function
* Rotates camera left/right.
*/
void APlayerCharacter::CallTurn(float Value) {
	this->AddControllerYawInput(Value);
}

/*
* CallJump function
* Makes character jump.
*/
void APlayerCharacter::CallJump() {
	this->Jump();
}

/*
* Shoot function
* Function handles shooting both for the player but also the ai.
* When the player calls the function, it checks if there are enough bullets before shooting.
* If the ai calls the function, it always shoots.
*/
void APlayerCharacter::Shoot() {
	AController* ControllerRef = GetController();
	if (ControllerRef->IsA(APC_PlayerController::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("player"));
		APC_PlayerController* playerController = Cast<APC_PlayerController>(ControllerRef);
		int bullets = playerController->GetBullets();
		if (bullets > 0)
			playerController->SetBullets(bullets--);
		else
			return;
	}
	FVector CameraLocation;
	FRotator CameraRotation;
	ControllerRef->GetPlayerViewPoint(CameraLocation, CameraRotation);
	FVector end = CameraLocation + CameraRotation.Vector() * 10000.0f;
	// Want to ignore who ever is the shooter.
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	FHitResult hit;
	bool hitSomething = GetWorld()->LineTraceSingleByChannel(hit, CameraLocation, end, ECC_Visibility, params);
	if (hitSomething) {
		// Since ECC_Visibility channel can be blocked by non actor objects,
		// check whether an actor was hit before applying damage.
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
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("%d"), Health);
	if (Health <= 0) {
		if (this->GetController()->IsA(APC_PlayerController::StaticClass()))
			Cast<AAssignmentGameModeBase>(UGameplayStatics::GetGameMode(this))->GameOver(false);
		this->Destroy();
	}
	return DamageAmount;
} 

/*
* GetHealth function
* Called from blueprints. Returns player's health.
*/
int APlayerCharacter::GetHealth() {
	return Health;
}

/*
* ThrowGrenade function
* Throw grenade
*/
void APlayerCharacter::ThrowGrenade() {
	AController* ControllerRef = GetController();
	if (ControllerRef == nullptr)
		return;
	APC_PlayerController* playerController = Cast<APC_PlayerController>(ControllerRef);
	int grenades = playerController->GetGrenades();
	if (grenades > 0)
		playerController->SetGrenades(grenades - 1);
	else
		return;
	if (GrenadeClass) {
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AGrenade* Grenade = GetWorld()->SpawnActor<AGrenade>(GrenadeClass, SpawnLocation, SpawnRotation);
		Grenade->SetOwner(this);
	}
}