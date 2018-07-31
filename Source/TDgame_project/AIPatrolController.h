// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class TDGAME_PROJECT_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category= "AI")
	UBehaviorTreeComponent* BehaviorComp;
	UPROPERTY(EditAnywhere, Category = "AI")
	UBlackboardComponent* BlackboardComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PlayerKey;

	TArray<AActor*> PatrolPoints;

	virtual void Possess(APawn* Pawn) override;


public:
	AAIPatrolController();

	int32 CurrentPatrolPoint;

	void SetPlayerCaught(APawn* Pawn);

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor* >GetPatrolPoint() const { return PatrolPoints; }
	
	
};
