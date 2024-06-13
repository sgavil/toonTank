// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksPlayerController::SetPlayerEnabled(bool IsEnabled)
{
	if (IsEnabled) {
		GetPawn()->EnableInput(this);
	}
	else {
		GetPawn()->DisableInput(this);

	}
	bShowMouseCursor = IsEnabled;
}
