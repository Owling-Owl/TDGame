// Fill out your copyright notice in the Description page of Project Settings.

#include "TDTowerBase.h"
#include "AIPatrol.h"
#include "Classes/Components/SphereComponent.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"
#include "Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ATDTowerBase::ATDTowerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static Mesh
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	RootComponent = TowerMesh;

	// Attack Range
	TowerAttackArea = CreateDefaultSubobject<USphereComponent>(TEXT("TowerAttackArea"));
	TowerAttackArea->SetupAttachment(TowerMesh);
	TowerAttackRange = 1000.f;
	TowerAttackArea->SetSphereRadius(TowerAttackRange);

	// Fire Effect
	TowerFireEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("TowerFireEffect"));

	// Tower Basic Parameters
	TowerDamage = 500.f;
	TowerAttackPeriod = 1.f;
	EnemySpeed = -1.f;

	// On clicked event
	OnClicked.AddDynamic(this, &ATDTowerBase::ShowAttackRange);
}

// Called when the game starts or when spawned
void ATDTowerBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(AttackTimer, this, &ATDTowerBase::TowerAttack, TowerAttackPeriod, true, 0.f);
}

void ATDTowerBase::TowerAttack()
{
	TArray<AActor*> AllTargets;
	TArray<AAIPatrol*> AllEnemies;
	TowerAttackArea->GetOverlappingActors(AllTargets);

	// Get Overlapping Enemies
	for (int32 iTarget = 0; iTarget < AllTargets.Num(); iTarget++)
	{
		if (AllTargets[iTarget]->GetClass()->IsChildOf(AAIPatrol::StaticClass()))
		{
			AllEnemies.Emplace(Cast<AAIPatrol>(AllTargets[iTarget]));
		}
	}

	// If Enemy exist, attack emeny
	if (AllEnemies.Num() > 0)
	{
		if (AllEnemies[0] && !IsPendingKill())
		{
			if (AllEnemies[0]->GetCurrentHealth() > 0)
			{
				AllEnemies[0]->UpdateHealth(-TowerDamage);
				if (EnemySpeed != -1)
				{
					AllEnemies[0]->UpdateSpeed(EnemySpeed);
				}
				TowerFire(AllEnemies[0]->GetActorLocation());
				AllEnemies[0]->IsAlive();
			}
		}
	}
}

void ATDTowerBase::TowerFire(FVector Location)
{
	UWorld* const World = GetWorld();
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString::SanitizeFloat(Location.X) + FString::FString(" ") + FString::SanitizeFloat(Location.Y) + FString::FString(" ") + FString::SanitizeFloat(Location.Z));
	UGameplayStatics::SpawnEmitterAtLocation(World, TowerFireEffect, Location, FRotator(0, 0, 0), FVector(1,1,1),false);

}

void ATDTowerBase::ShowAttackRange(AActor * tower, FKey key)
{
	if (TowerAttackArea->bHiddenInGame)
		TowerAttackArea->SetHiddenInGame(false);
	else
		TowerAttackArea->SetHiddenInGame(true);
}

// Called every frame
void ATDTowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}