// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "FinishLine.h"
#include "AI_TD_EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TDGAME_PROJECT_API AAI_TD_EnemyController : public AAIController
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category="AI")
	UBlackboardComponent* BlackboardComp;
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTreeComponent* BehaviorComp;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;
	UPROPERTY(EditAnywhere, Category = "AI")
	FVector LocationToGo;


	virtual void Possess(APawn* Pawn) override;

public:
	AAI_TD_EnemyController();


	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE FVector GetLocationToGo() const { return LocationToGo; }
	
	UFUNCTION(BlueprintCallable, Category = "AI")
	FVector WhereToGo();
	AFinishLine* FinishLine;
private:
	TArray<AActor*> Target;
};
