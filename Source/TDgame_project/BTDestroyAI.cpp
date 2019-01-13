// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDestroyAI.h"
#include "Kismet/GameplayStatics.h"
#include "Camera.h"
#include "AI_TD_EnemyController.h"


EBTNodeResult::Type UBTDestroyAI::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AAI_TD_EnemyController* AIController = Cast<AAI_TD_EnemyController>(OwnerComp.GetAIOwner());
	if (AIController&&AIController->GetPawn())
	{

		ACamera* Controller = Cast<ACamera>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
		Controller->UpdateLife(-1);
		if (Controller->GetCurrentLife() <= 0)
		{
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(1);
		
		}
		AIController->GetPawn()->Destroy();
		AIController->Destroy();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}



