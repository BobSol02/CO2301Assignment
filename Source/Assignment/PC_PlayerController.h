// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacter.h"
#include "PC_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_API APC_PlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	// Start Screen variables
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StartScreenClass;
	UPROPERTY()
	UUserWidget* StartScreen;

	// Game Won Screen variables
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameWonScreenClass;
	UPROPERTY()
	UUserWidget* GameWonScreen;

	// Game Over Screen variables
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameOverScreenClass;
	UPROPERTY()
	UUserWidget* GameOverScreen;

	// HUD variables
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MiniMapClass;
	UPROPERTY()
	UUserWidget* MiniMap;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CrossClass;
	UPROPERTY()
	UUserWidget* Cross;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY()
	UUserWidget* HUD;

	UFUNCTION()
	void SetupLevelHUD();

	// Blueprint functions
	UFUNCTION(BlueprintCallable)
	void StartGame();
	UFUNCTION(BlueprintCallable)
	void Exit();

	// Player Variables
	UPROPERTY(EditAnywhere)
	int NumberOfBullets = 0;
public:
	UFUNCTION(BlueprintPure)
	int GetBullets();
	UFUNCTION()
	void SetBullets(int num);
};
