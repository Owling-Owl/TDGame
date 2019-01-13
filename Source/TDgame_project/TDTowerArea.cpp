// Fill out your copyright notice in the Description page of Project Settings.

#include "TDTowerArea.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATDTowerArea::ATDTowerArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup area
	TowerAreaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerAreaMesh"));
	RootComponent = TowerAreaMesh;

	OnSelectedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OnSelectedMaterial"));
	MouseOverBeginMaterial = CreateDefaultSubobject<UMaterial>(TEXT("MouseOverBeginMaterial"));
	MouseOverEndMaterial = CreateDefaultSubobject<UMaterial>(TEXT("MouseOverEndMaterial"));

	CanSpawnTower = true;
	OnClicked.AddDynamic(this, &ATDTowerArea::BuildTower);
	TowerAreaMesh->OnBeginCursorOver.AddDynamic(this, &ATDTowerArea::MouseOverBegin);
	TowerAreaMesh->OnEndCursorOver.AddDynamic(this, &ATDTowerArea::MouseOverEnd);
}

// Called when the game starts or when spawned
void ATDTowerArea::BeginPlay()
{
	Super::BeginPlay();
}

bool ATDTowerArea::GetCanSpawnTower()
{
	return CanSpawnTower;
}

void ATDTowerArea::SetCanSpawnTower(bool boolean)
{
	CanSpawnTower = boolean;
}

void ATDTowerArea::BuildTower(AActor* Tower, FKey key)
{
	if (CanSpawnTower)
	{
		TowerAreaMesh->SetMaterial(0, OnSelectedMaterial);
	}
}

void ATDTowerArea::MouseOverBegin(UPrimitiveComponent * Component)
{
	if (CanSpawnTower)
	{
		TowerAreaMesh->SetMaterial(0, MouseOverBeginMaterial);
	}
}

void ATDTowerArea::MouseOverEnd(UPrimitiveComponent * Component)
{

	TowerAreaMesh->SetMaterial(0, MouseOverEndMaterial);

}

// Called every frame
void ATDTowerArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
