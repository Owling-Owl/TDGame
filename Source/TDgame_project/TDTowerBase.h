// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIPatrol.h"
#include "ParticleDefinitions.h"
#include "TDTowerBase.generated.h"


UCLASS()
class TDGAME_PROJECT_API ATDTowerBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATDTowerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Attack Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
		float TowerDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
		float EnemySpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
		float TowerAttackRange;
	UFUNCTION(BlueprintCallable, Category = "Tower")
		void TowerAttack();

	// Fire Effect
	UFUNCTION(BlueprintCallable, Category = "Tower")
		void TowerFire(FVector Location);

	// Attack Speed
	FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
		float TowerAttackPeriod;

	// Show Attack Range
	UFUNCTION(BlueprintCallable, Category = "Tower")
		void ShowAttackRange(AActor* tower, FKey key);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return TowerMesh; }
	FORCEINLINE class USphereComponent* GetAttackArea() const { return TowerAttackArea; }


private:
	// Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tower, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TowerMesh;

	// Attack Area
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tower, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* TowerAttackArea;

	// Fire Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tower, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* TowerFireEffect;
	
};
