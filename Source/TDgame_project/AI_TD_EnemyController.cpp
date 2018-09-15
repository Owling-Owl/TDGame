// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_TD_EnemyController.h"
#include "AIPatrol.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"



AAI_TD_EnemyController::AAI_TD_EnemyController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	//Initialize blackboard key
	LocationToGoKey = "LocationToGo";
	LocationToGo = { 0,0,0 };


}
FVector AAI_TD_EnemyController::WhereToGo()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFinishLine::StaticClass(), Target);
	FinishLine = Cast<AFinishLine>(Target[0]);
	LocationToGo = FinishLine->SetRandomPoint();
	return FVector(LocationToGo);
}


void AAI_TD_EnemyController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);
	AAIPatrol* AICharacter = Cast<AAIPatrol>(Pawn);
	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}
		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Started"));
	}
	
}

