// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLAttributeComponent.h"

// Sets default values for this component's properties
UBDLAttributeComponent::UBDLAttributeComponent() : MaxHealth(100.f), Health(MaxHealth)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}

bool UBDLAttributeComponent::IsAlive()
{
	return Health > 0.0f;
}


bool UBDLAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}
