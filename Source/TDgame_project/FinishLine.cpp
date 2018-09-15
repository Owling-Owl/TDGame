// Fill out your copyright notice in the Description page of Project Settings.

#include "FinishLine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "AI_TD_EnemyController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AIPatrol.h"


// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Destination = CreateDefaultSubobject<UBoxComponent>(TEXT("Destination"));
	RootComponent = Destination;

}



// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AFinishLine::SetRandomPoint()
{
	FVector VolumeOrigin = Destination->Bounds.Origin;
	FVector VolumeExtent = Destination->Bounds.BoxExtent;
	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(VolumeOrigin, VolumeExtent);
	RandomPoint.Z = VolumeOrigin.Z ;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Located"));
	return RandomPoint;
}