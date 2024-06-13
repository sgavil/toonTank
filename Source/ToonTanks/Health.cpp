#include "Health.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UHealth::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealth::DamageTaken);
	GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

}


void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealth::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.F || Health <= 0.F) return;

	Health -= Damage;
	if (Health <= 0.F && GameMode) {
		GameMode->ActorDied(DamagedActor);
	}
	
}

