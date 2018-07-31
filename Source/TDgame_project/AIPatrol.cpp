// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "Engine.h"


// Sets default values
AAIPatrol::AAIPatrol()
{
 	//initialize sensing component
	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComp"));
	SensingComp->SetPeripheralVisionAngle(70.0f);
	Health = 1000.0f;
}

// Called when the game starts or when spawned
void AAIPatrol::BeginPlay()
{
	Super::BeginPlay();
	if (SensingComp)
	{
		SensingComp->OnSeePawn.AddDynamic(this, &AAIPatrol::OnPlayerCaught);
	}
}

// Called every frame


// Called to bind functionality to input
void AAIPatrol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIPatrol::OnPlayerCaught(APawn* Pawn)
{
	//get ref to the playercontroller
	AAIPatrolController* AIController = Cast<AAIPatrolController>(GetController());
	if (AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("You have been caught!"));
		AIController->SetPlayerCaught(Pawn);
	}


}
float AAIPatrol::GetCurrentHealth()
{
	return Health;
}
void AAIPatrol::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
}
void AAIPatrol::IsAlive() 
{
	if (Health <= 0)
	{
		Destroy();
	}
}
