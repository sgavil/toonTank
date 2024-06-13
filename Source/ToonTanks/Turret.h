#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"


UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	void HandleDestruction() override;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	bool IsInRange();

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ActionRange{ 700.F };

	class ATank* Tank;

	FTimerHandle FireTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate{ 2.F};
	void CheckCanFire();
};
