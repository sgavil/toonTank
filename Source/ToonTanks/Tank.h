// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction() override;

	APlayerController* GetPlayerController() const { return PlayerControllerRef; }

	bool bAlive{ true };

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed{ 10.F };

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed{ 10.F };

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent{ nullptr };
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent{ nullptr };

	APlayerController* PlayerControllerRef{ nullptr };

	void Move(float Value);
	void Turn(float Value);





};
