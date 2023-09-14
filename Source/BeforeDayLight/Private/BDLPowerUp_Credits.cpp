// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLPowerUp_Credits.h"

#include "BDLPlayerState.h"


ABDLPowerUp_Credits::ABDLPowerUp_Credits()
{
	
	CreditsAmount = 80;
}

void ABDLPowerUp_Credits::Interact_Implementation(APawn* InstigatorPawn)
{
	if(!ensure(InstigatorPawn))
	{
		return;
	}

	if(ABDLPlayerState* PS = InstigatorPawn->GetPlayerState<ABDLPlayerState>())
	{
		PS->AddCredits(CreditsAmount);
		HideAndCooldownPowerup();
	}

}

