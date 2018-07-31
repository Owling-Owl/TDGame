// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIPatrol.generated.h"

UCLASS()
class TDGAME_PROJECT_API AAIPatrol : public ACharacter
{
	GENERATED_BODY()

		

public:
	// Sets default values for this character's properties
	AAIPatrol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,Category = "HP")
	float Health;

public:	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* SensingComp;

	//get CurrentPower
	UFUNCTION(BlueprintPure, Category = "HP")
	float GetCurrentHealth();
	//Upadate
	UFUNCTION(BlueprintCallable, Category = "HP")
	void UpdateHealth(float HealthChange);

	UFUNCTION(BlueprintCallable, Category = "HP")
	void IsAlive();

private:
	UFUNCTION(BlueprintCallable,Category = "AI")
	void OnPlayerCaught(APawn* Pawn);
};
