// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDTowerArea.generated.h"

UCLASS()
class TDGAME_PROJECT_API ATDTowerArea : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATDTowerArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Build Tower
	bool CanSpawnTower;
	UFUNCTION(BlueprintPure, Category = "TowerArea")
		bool GetCanSpawnTower();
	UFUNCTION(BlueprintCallable, Category = "TowerArea")
		void SetCanSpawnTower(bool boolean);

	UFUNCTION(BlueprintCallable, Category = "TowerArea")
		void BuildTower(AActor* Tower, FKey key);

	UFUNCTION(BlueprintCallable, Category = "TowerArea")
		void MouseOverBegin(UPrimitiveComponent* Component);
	UFUNCTION(BlueprintCallable, Category = "TowerArea")
		void MouseOverEnd(UPrimitiveComponent* Component);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TowerArea", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TowerAreaMesh;

	// Material
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerArea", meta = (AllowPrivateAccess = "true"))
		class UMaterial* OnSelectedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerArea", meta = (AllowPrivateAccess = "true"))
		class UMaterial* MouseOverBeginMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerArea", meta = (AllowPrivateAccess = "true"))
		class UMaterial* MouseOverEndMaterial;
};