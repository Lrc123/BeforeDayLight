// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLPowerup_HealthPotion.h"

#include "BDLAttributeComponent.h"
#include "BDLPlayerState.h"


//#define LOCTEXT_NAMESPACE "InteractableActors"
ABDLPowerup_HealthPotion::ABDLPowerup_HealthPotion()
{
	CreditCost = 50;
}

void ABDLPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if(!ensure(InstigatorPawn))
	{
		return;
	}

	UBDLAttributeComponent* AttributeComp = UBDLAttributeComponent::GetAttributes(InstigatorPawn);

	if(ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if(ABDLPlayerState* PS = InstigatorPawn->GetPlayerState<ABDLPlayerState>()){
			if(PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, 50.f))
			{
				 HideAndCooldownPowerup();
			}
		}
		
		//return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full Health");
	}
	//return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. Restores health to maximum."), CreditCost);
}

//#undef LOCTEXT_NAMESPACE 


