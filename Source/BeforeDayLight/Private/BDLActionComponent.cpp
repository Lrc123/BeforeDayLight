// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLActionComponent.h"


UBDLActionComponent::UBDLActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UBDLActionComponent::BeginPlay()
{
	Super::BeginPlay();
	for(TSubclassOf<UBDLAction> ActionClass: DefaultActions)
	{
		AddAction(ActionClass);
	}
}


void UBDLActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UBDLActionComponent::AddAction(TSubclassOf<UBDLAction> ActionClass)
{
	// this is just a class, not reference to an instance
	if(!ensure(ActionClass))
	{
		return;
	}

	// Instantiate the class and add it to our action array
	UBDLAction* NewAction = NewObject<UBDLAction>(this, ActionClass);
	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
	
}

bool UBDLActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for(UBDLAction* Action: Actions)
	{
		if(Action && Action->ActionName == ActionName)
		{
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UBDLActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for(UBDLAction* Action: Actions)
	{
		if(Action && Action->ActionName == ActionName)
		{
			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;
}

