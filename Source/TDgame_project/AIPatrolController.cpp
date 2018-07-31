// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPatrolController.h"
#include "AIPatrol.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"
#include "AIPatrolPoint.h"

AAIPatrolController::AAIPatrolController()
{
	//Initialize BB and BT 
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	//Initialize blackboard key
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";

	CurrentPatrolPoint = 0;

}

void AAIPatrolController::SetPlayerCaught(APawn * Pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
	}
}

void AAIPatrolController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	//Get reference to character 
	AAIPatrol* AICharacter = Cast<AAIPatrol>(Pawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
	}
}


