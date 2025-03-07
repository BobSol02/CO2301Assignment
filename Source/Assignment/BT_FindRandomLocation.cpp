// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

/*
* UBT_FindRandomLocation::ExecuteTask function
* Finds a random reachable location.
*/
EBTNodeResult::Type UBT_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed; 
	}
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	float RandomRadius = 500.0f;
	FNavLocation RandomLocation;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	NavSys->GetRandomReachablePointInRadius(AIActor->GetActorLocation(), RandomRadius, RandomLocation);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPosition"), RandomLocation);

	return EBTNodeResult::Succeeded;
}