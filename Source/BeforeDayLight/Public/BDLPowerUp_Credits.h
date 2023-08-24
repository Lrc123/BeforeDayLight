// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLPowerUpActor.h"
#include "BDLPowerUp_Credits.generated.h"

/**
 * 
 */
UCLASS()
class BEFOREDAYLIGHT_API ABDLPowerUp_Credits : public ABDLPowerUpActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Credits")
	int32 CreditsAmount;

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	ABDLPowerUp_Credits();
	
};
