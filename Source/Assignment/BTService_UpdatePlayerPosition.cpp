// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerPosition.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

/*
* UBTService_UpdatePlayerPosition::TickNode function
* Sets the player position in blackboard.
*/
void UBTService_UpdatePlayerPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}
