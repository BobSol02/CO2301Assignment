// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_PlayerController.h"
#include "Kismet/GameplayStatics.h"

/*
* BeginPlay function
* Is loaded every time a new level starts. Loads different widgets depending on the level.
*/
void APC_PlayerController::BeginPlay() {
	Super::BeginPlay();

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
		// If the number of grenades has not been altered from the editor, set to a default value of 5
		if (!NumberOfGrenades) {
			NumberOfGrenades = 5;
		}
		SetupLevelHUD();
	}
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "GameWon") {
		GameWonScreen = CreateWidget(this, GameWonScreenClass);
		if (GameWonScreen != nullptr)
			GameWonScreen->AddToViewport();
	}
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "GameOver") {
		GameOverScreen = CreateWidget(this, GameOverScreenClass);
		if (GameOverScreen != nullptr)
			GameOverScreen->AddToViewport();
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
* StartGame Function
* Called from blueprints. Begins the game.
*/
void APC_PlayerController::StartGame() {
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) != "Level") {
		if (StartScreen != nullptr)
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

/*
* MainMenu Function
* Called from blueprints. Goes to main menu
*/
void APC_PlayerController::MainMenu() {
	if (GameWonScreen != nullptr)
		GameWonScreen->RemoveFromViewport();
	if (GameOverScreen != nullptr)
		GameOverScreen->RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), "Start");
}

/*
* GetGrenades function
* Called from blueprints. Returns number of grenades.
*/
int APC_PlayerController::GetGrenades() {
	return NumberOfGrenades;
}

/*
* SetGrenades function
* Used from other classes. Sets number of grenades to a new value.
*/
void APC_PlayerController::SetGrenades(int num) {
	NumberOfGrenades = num;
}