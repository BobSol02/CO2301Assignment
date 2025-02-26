// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
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
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MiniMapClass;
	UPROPERTY()
	UUserWidget* MiniMap;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CrossClass;
	UPROPERTY()
	UUserWidget* Cross;
};
