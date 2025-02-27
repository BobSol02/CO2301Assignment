// Copyright Epic Games, Inc. All Rights Reserved.


#include "AssignmentGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AAssignmentGameModeBase::BeginPlay() {
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Level")
		AAssignmentGameModeBase::StartGame();
}

void AAssignmentGameModeBase::StartGame() {
	UE_LOG(LogTemp, Warning, TEXT("Start Game"));
	// If game duration not set in editor, set it to 60
	if (!GameDuration)
		GameDuration = 60.0f;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AAssignmentGameModeBase::TimeUp, GameDuration, false);
}

void AAssignmentGameModeBase::TimeUp() {
	UE_LOG(LogTemp, Warning, TEXT("Time Up"));
	GameOver(false);
}

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
* Called from blueprints. Returns time formatted to minutes and seconds
*/
FString AAssignmentGameModeBase::GetTime() {
	float timeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(Timer);
	return ((timeRemaining>=60)?FString::FromInt((int)(timeRemaining / 60))+FString(":") : FString(""))
		+ (((int)(timeRemaining) % 60>=10)?FString::FromInt((int)(timeRemaining)%60): FString::FromInt(0) + FString::FromInt((int)(timeRemaining) % 60));
}
