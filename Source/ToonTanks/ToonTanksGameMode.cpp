#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DiedActor)
{
	if (Tank == DiedActor) {
		Tank->HandleDestruction();
		if (ToonTanksPlayerController) {
			ToonTanksPlayerController->SetPlayerEnabled(false);
			GameOver(false);
		}
	}
	else if (auto DiedTurret = Cast<class ATurret>(DiedActor)) {
		DiedTurret->HandleDestruction();
		TargetTowers--;
		if (TargetTowers <= 0) {
			GameOver(true);
		}
	}

}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	TargetTowers = GetTargetTowerCount();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast< AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController) {
		ToonTanksPlayerController->SetPlayerEnabled(false);

		FTimerHandle PlayeEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabled, true);
		GetWorldTimerManager().SetTimer(PlayeEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), OutActors); 
	return OutActors.Num();
}
