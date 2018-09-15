// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FinishLine.h"
#include "BTSelectDestination.generated.h"

/**
 * 
 */
UCLASS()
class TDGAME_PROJECT_API UBTSelectDestination : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory) override;
	
	
};
