// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterMesh = GetMesh();
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CharacterMesh);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
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