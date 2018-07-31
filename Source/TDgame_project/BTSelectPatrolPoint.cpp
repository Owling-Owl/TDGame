// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSelectPatrolPoint.h"
#include "AIPatrolController.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* AIController = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		//get bbcomp
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();

		AAIPatrolPoint* CurrentPoint = Cast<AAIPatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailablePatrolPoints = AIController->GetPatrolPoint();

		AAIPatrolPoint* NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[0]);

		if (AIController->CurrentPatrolPoint != AvailablePatrolPoints.Num()-1)
		{
			NextPatrolPoint = 
				Cast<AAIPatrolPoint>(AvailablePatrolPoints[++AIController->CurrentPatrolPoint]);
		}
		else //if there is not any more point to go to
		{
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[0]);
			AIController->CurrentPatrolPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
