// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera.h"
#include "CameraMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACamera::ACamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Camera
	CameraCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CameraCollision->SetupAttachment(RootComponent);
	CameraCollision->InitSphereRadius(50.f);
	CameraCollision->SetCollisionProfileName(TEXT("Pawn"));

	CameraPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	CameraPoint->SetupAttachment(CameraCollision);
	CameraPoint->SetWorldRotation(FRotator(-45.f, 0.f, 0.f));

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraArm->SetupAttachment(CameraPoint);
	CameraArm->TargetArmLength = 1500.f;
	CurrentSpringArm = 750.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm);
	DisableCamNav = false;

	// Move
	OurMovementComponent = CreateDefaultSubobject<UCameraMovementComponent>(TEXT("MovementComponent"));
	OurMovementComponent->SetUpdatedComponent(RootComponent);

	//initialize
	LivesOfLevel = 10;
}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();

}

UPawnMovementComponent * ACamera::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACamera::MoveX(float Value)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * Value);
	}
}

void ACamera::MoveY(float Value)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * Value);
	}
}

void ACamera::MoveZ(float Value)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorUpVector() * Value);
	}
}

void ACamera::ZoomIn()
{
	float ZoomInRate = 100.0f;
	CurrentSpringArm -= ZoomInRate;

	if (CurrentSpringArm <= 100.0f)
	{
		CameraArm->TargetArmLength = 100.0f;
		CurrentSpringArm = 100.0f;
	}
	else
	{
		CameraArm->TargetArmLength = CurrentSpringArm;
	}
}

void ACamera::ZoomOut()
{
	float ZoomOutRate = 100.f;
	CurrentSpringArm += ZoomOutRate;

	if (CurrentSpringArm >= 3000.0f)
	{
		CameraArm->TargetArmLength = 3000.0f;
		CurrentSpringArm = 3000.0f;
	}
	else
	{
		CameraArm->TargetArmLength = CurrentSpringArm;
	}
}

void ACamera::PanPressed()
{
	DisableCamNav = false;
}

void ACamera::PanReleased()
{
	DisableCamNav = true;
}

void ACamera::UpdateLife(int Value)
{
	LivesOfLevel += Value;
}

int ACamera::GetCurrentLife()
{
	return LivesOfLevel;
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Camera
	if (!DisableCamNav)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());

		FVector2D MouseDelta;
		PC->GetInputMouseDelta(MouseDelta.X, MouseDelta.Y);

		FRotator NewRotation = GetActorRotation();

		if (MouseDelta.X != 0 || MouseDelta.Y != 0)
		{
			NewRotation.Yaw += MouseDelta.X * 2;
			SetActorRotation(NewRotation);

			float Pitch = CameraPoint->GetComponentRotation().Pitch;
			float Yaw = CameraPoint->GetComponentRotation().Yaw;
			float Roll = CameraPoint->GetComponentRotation().Roll;
			Pitch += MouseDelta.Y * 2;

			CameraPoint->SetWorldRotation(FRotator(FMath::Clamp(Pitch, -60.f, -5.f), Yaw, Roll));
		}
	}
}

// Called to bind functionality to input
void ACamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ACamera::MoveX);
	InputComponent->BindAxis("MoveY", this, &ACamera::MoveY);
	InputComponent->BindAxis("MoveZ", this, &ACamera::MoveZ);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACamera::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACamera::ZoomOut);

	InputComponent->BindAction("Pan", IE_Pressed, this, &ACamera::PanPressed);
	InputComponent->BindAction("Pan", IE_Released, this, &ACamera::PanReleased);
}
