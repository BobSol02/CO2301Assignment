// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AssignmentGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API AAssignmentGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void GameOver(bool win);
	UPROPERTY()
	FTimerHandle Timer;
	UPROPERTY(EditAnywhere)
	float GameDuration = 0;
	UFUNCTION()
	void TimeUp();
	UFUNCTION(BlueprintPure)
	FString GetTime();
protected:
	virtual void BeginPlay() override;
};
