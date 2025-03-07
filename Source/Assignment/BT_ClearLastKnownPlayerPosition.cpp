// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_ClearLastKnownPlayerPosition.h"
#include "BehaviorTree/BlackboardComponent.h"

/*
* UBT_ClearLastKnownPlayerPosition::ExecuteTask function
* Clears last known player position from blackboard.
*/
EBTNodeResult::Type UBT_ClearLastKnownPlayerPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->ClearValue("LastKnownPlayerPosition");
	return EBTNodeResult::Succeeded;
}