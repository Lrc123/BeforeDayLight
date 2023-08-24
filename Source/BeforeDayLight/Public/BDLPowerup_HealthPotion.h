// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLPowerUpActor.h"
#include "BDLPowerup_HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class BEFOREDAYLIGHT_API ABDLPowerup_HealthPotion : public ABDLPowerUpActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="HealthPotion")
	int32 CreditCost;

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	ABDLPowerup_HealthPotion();
	
};
