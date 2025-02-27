// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_PlayerController.h"
#include "Kismet/GameplayStatics.h"

void APC_PlayerController::BeginPlay() {
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("abc: %s"), *UGameplayStatics::GetCurrentLevelName(GetWorld()));
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Start") {
		StartScreen = CreateWidget(this, StartScreenClass);
		if (StartScreen != nullptr)
			StartScreen->AddToViewport();
	}
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Level") {
		// If the number of bullets has not been altered from the editor, set to a default value of 50
		if (!NumberOfBullets) {
			NumberOfBullets = 50;
		}
		SetupLevelHUD();
	}
}

/*
* SetupLevelHUD function
* Main responsibility of the function to setup the main level HUD.
* No need to setup everything if the player chooses to not start the game.
*/
void APC_PlayerController::SetupLevelHUD() {
	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
		HUD->AddToViewport();
	
	MiniMap = CreateWidget(this, MiniMapClass);
	if (MiniMap != nullptr)
		MiniMap->AddToViewport();

	Cross = CreateWidget(this, CrossClass);
	if (Cross != nullptr)
		Cross->AddToViewport();
}

/*
* Start Game Function
* Called from blueprints. Begins the game.
*/
void APC_PlayerController::StartGame() {
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) != "Level") {
		//UE_LOG(LogTemp, Warning, TEXT("Cool: %s"), *UGameplayStatics::GetCurrentLevelName(GetWorld()));
		StartScreen->RemoveFromViewport();
		UGameplayStatics::OpenLevel(GetWorld(), "Level");
	}
}

/*
* Exit Function
* Called from blueprints. Quits the game.
* https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/GenericPlatform/FGenericPlatformMisc/RequestExit?application_version=5.5
*/
void APC_PlayerController::Exit() {
	FGenericPlatformMisc::RequestExit(false);
}

/*
* GetBullets function
* Called from blueprints. Returns number of bullets.
*/
int APC_PlayerController::GetBullets() {
	return NumberOfBullets;
}

/*
* SetBullets function
* Used from other classes. Sets number of bullets to a new value.
*/
void APC_PlayerController::SetBullets(int num) {
	NumberOfBullets = num;
}