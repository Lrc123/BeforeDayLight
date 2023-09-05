// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLAttributeComponent.h"

#include "BDLGameModeBase.h"
#include "MathUtil.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("bdl.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

// Sets default values for this component's properties
UBDLAttributeComponent::UBDLAttributeComponent() : MaxHealth(100.f), Health(MaxHealth)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

bool UBDLAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetMaxHealth());
}


bool UBDLAttributeComponent::IsAlive()
{
	return Health > 0.0f;
}


bool UBDLAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if(!GetOwner()->CanBeDamaged() && Delta < 0.f)
	{
		return false;
	}

	/*
	if(InstigatorActor == GetOwner()->GetInstigator())
	{
		return false;
	}
	*/
	
	if(Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta*=DamageMultiplier;
	}
	
	float OldHealth = Health;
	Health = FMathf::Clamp(Health + Delta, 0.0f, MaxHealth);
	float ActualDeltaHealth = Health - OldHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

	if(ActualDeltaHealth < 0.0f && Health == 0.0f)
	{
		ABDLGameModeBase* GM = GetWorld()->GetAuthGameMode<ABDLGameModeBase>();
		if(GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return ActualDeltaHealth != 0;
}

bool UBDLAttributeComponent::IsFullHealth() const
{
	return MaxHealth == Health;
}

bool UBDLAttributeComponent::IsActorAlive(AActor* Actor)
{
	UBDLAttributeComponent* AttributeComp = GetAttributes(Actor);
	if(AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	return false;
}

UBDLAttributeComponent* UBDLAttributeComponent::GetAttributes(AActor* FromActor)
{
	if(FromActor){
		return FromActor->FindComponentByClass<UBDLAttributeComponent>();
	}
	return nullptr;
}

float UBDLAttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UBDLAttributeComponent::GetCurHealth() const
{
	return Health;
}


