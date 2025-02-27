// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Fire.h"
#include "AIController.h"
#include "PlayerCharacter.h"

/*
* UBT_Fire::ExecuteTask function
* AI fire task. Uses shooting functionality from character class
*/
EBTNodeResult::Type UBT_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	if (AIActor->IsA(APlayerCharacter::StaticClass())) {
		APlayerCharacter* Character = (APlayerCharacter*)AIActor;
		Character->Shoot();
		UE_LOG(LogTemp, Warning, TEXT("Fire success"));
		return EBTNodeResult::Succeeded;
	}
	UE_LOG(LogTemp, Warning, TEXT("Fire failed"));
	return EBTNodeResult::Failed;
}
