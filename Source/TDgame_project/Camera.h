// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera.generated.h"

UCLASS()
class TDGAME_PROJECT_API ACamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UCameraMovementComponent* OurMovementComponent;
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	// 3D Move
	void MoveX(float Value);
	void MoveY(float Value);
	void MoveZ(float Value);

	// Camera Zoom
	void ZoomIn();
	void ZoomOut();
	float CurrentSpringArm;

	// Pan Move
	void PanPressed();
	void PanReleased();
	bool DisableCamNav;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	int LivesOfLevel;
	UFUNCTION(BlueprintCallable, Category = "Life")
	void UpdateLife(int Value);
	UFUNCTION(BlueprintPure, Category = "Life")
	int GetCurrentLife();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* CameraScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CameraCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* CameraPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
};