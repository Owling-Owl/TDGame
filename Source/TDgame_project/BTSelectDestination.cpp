// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSelectDestination.h"
#include "AI_TD_EnemyController.h"
#include "FinishLine.h"
#include "AIPatrol.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTSelectDestination::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAI_TD_EnemyController* AIController = Cast<AAI_TD_EnemyController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();
		FVector Location = BlackboardComp->GetValueAsVector("LocationToGo");
		Location = AIController->WhereToGo();
		BlackboardComp->SetValueAsVector("LocationToGo", Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
