// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

/*
* BeginPlay function
* Loads behaviour tree for ai. 
*/
void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();
	RunBehaviorTree(BehaviourTree);
}