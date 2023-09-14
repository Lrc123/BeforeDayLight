// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLAction.h"
#include "BDLPowerUpActor.h"
#include "BDLPowerUp_Action.generated.h"

/**
 * 
 */
UCLASS()
class BEFOREDAYLIGHT_API ABDLPowerUp_Action : public ABDLPowerUpActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Powerup")
	TSubclassOf<UBDLAction> ActionToGrant;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;
};
