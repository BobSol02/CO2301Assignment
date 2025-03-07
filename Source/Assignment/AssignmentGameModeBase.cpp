// Copyright Epic Games, Inc. All Rights Reserved.


#include "AssignmentGameModeBase.h"
#include "Kismet/GameplayStatics.h"

/*
* BeginPlay function
* As the function gets called every time a level gets loaded, it only loads StartGame when in the main level.
*/
void AAssignmentGameModeBase::BeginPlay() {
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Level")
		AAssignmentGameModeBase::StartGame();
}

/*
* StartGame function
* Function sets up the game.
*/
void AAssignmentGameModeBase::StartGame() {
	UE_LOG(LogTemp, Warning, TEXT("Start Game"));
	// If game duration not set in editor, set it to 300
	if (!GameDuration)
		GameDuration = 300.0f;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AAssignmentGameModeBase::TimeUp, GameDuration, false);
}

/*
* TimeUp function
* Used in SetTimer when the game time runs out.
*/
void AAssignmentGameModeBase::TimeUp() {
	UE_LOG(LogTemp, Warning, TEXT("Time Up"));
	GameOver(false);
}

/*
* GameOver function
* Brings up correct screen depending on whether the player won or lost.
*/
void AAssignmentGameModeBase::GameOver(bool win) {
	if (win) {
		UE_LOG(LogTemp, Warning, TEXT("Victory"));
		UGameplayStatics::OpenLevel(GetWorld(), "GameWon");
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Game Over"));
		UGameplayStatics::OpenLevel(GetWorld(), "GameOver");
	}
}

/*
* GetTime function
* Called from blueprints. Returns time formatted to minutes and seconds.
*/
FString AAssignmentGameModeBase::GetTime() {
	float timeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(Timer);
	return ((timeRemaining>=60)?FString::FromInt((int)(timeRemaining / 60))+FString(":") : FString(""))
		+ (((int)(timeRemaining) % 60>=10)?FString::FromInt((int)(timeRemaining)%60): FString::FromInt(0) + FString::FromInt((int)(timeRemaining) % 60));
}
