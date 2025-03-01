// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FireFromRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

/*
* UBTService_FireFromRange::TickNode function
* Service to check whether the distance of the ai is large enough to fire towards the player
*/
void UBTService_FireFromRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(EnemyAIController->GetPawn()->GetDistanceTo(PlayerPawn)));

	if (EnemyAIController->GetPawn()->GetDistanceTo(PlayerPawn)<1000.0f) {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}