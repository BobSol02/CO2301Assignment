// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LineOfSight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

/*
* UBTService_LineOfSight::TickNode function
* Checks if there is line of sight between ai and player.
*/
void UBTService_LineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = EnemyAIController->GetPawn();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector AIForwardVector = AIPawn->GetActorForwardVector();
	FVector PlayerPositionVector = PlayerPawn->GetActorLocation();
	FVector AIPositionVector = AIPawn->GetActorLocation();
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;
	AIToPlayerVector.Normalize();
	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);

	if (EnemyAIController->LineOfSightTo(PlayerPawn) && DirectionDotProduct>0) {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("LastKnownPlayerPosition", OwnerComp.GetBlackboardComponent()->GetValueAsVector("PlayerPosition"));
		OwnerComp.GetBlackboardComponent()->ClearValue("PlayerPosition");
	}
}
