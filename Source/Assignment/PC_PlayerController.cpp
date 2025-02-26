// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_PlayerController.h"

void APC_PlayerController::BeginPlay() {
	Super::BeginPlay();

	MiniMap = CreateWidget(this, MiniMapClass);

	if (MiniMap != nullptr)
		MiniMap->AddToViewport();

	Cross = CreateWidget(this, CrossClass);
	if (Cross != nullptr)
			Cross->AddToViewport();
}

