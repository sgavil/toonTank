#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Tank) {
		UE_LOG(LogTemp, Warning, TEXT("Tank component not found in turret"));
	}

	GetWorldTimerManager().SetTimer(FireTimerHandle,this, &ATurret::CheckCanFire, FireRate, true);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInRange()) {
		RotateTurret(Tank->GetActorLocation());
	}
}

bool ATurret::IsInRange()
{
	if (!Tank) return false;
	return FVector::Dist(Tank->GetActorLocation(), GetActorLocation()) <= ActionRange;
}

void ATurret::CheckCanFire()
{
	if (!Tank || !Tank->bAlive) return;
	if (IsInRange()) {
		Fire();
	}
}
