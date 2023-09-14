// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLActionComponent.h"
#include "BDLAction.h"
#include "BeforeDayLight/BeforeDayLight.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"


UBDLActionComponent::UBDLActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}


void UBDLActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Server Only
	if(GetOwner()->HasAuthority()){
		for(TSubclassOf<UBDLAction> ActionClass: DefaultActions)
		{
			AddAction(GetOwner(), ActionClass);
		}
	}
}


void UBDLActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);

	for(UBDLAction* Action: Actions)
	{
		FColor TextColor = Action->GetIsRunning() ? FColor::Blue : FColor::White;
		FString ActionMsg = FString::Printf(TEXT("[%s] Action: %s : IsRunning: %s : Outer: %s"),
			*GetNameSafe(GetOuter()),
			*Action->ActionName.ToString(),
			Action->GetIsRunning() ? TEXT("true") : TEXT("false"),
			*GetNameSafe(GetOuter()));
		LogOnScreen(this, ActionMsg, TextColor, 0.0f);
	}
		
}


void UBDLActionComponent::AddAction(AActor* Instigator, TSubclassOf<UBDLAction> ActionClass)
{
	// this is just a class, not reference to an instance
	if(!ensure(ActionClass))
	{
		return;
	}

	// Skip for clients
	if(!GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Client attempting to AddAction.[Class: %s]"), *GetNameSafe(ActionClass));
		return;
	}

	// Instantiate the class and add it to our action array
	UBDLAction* NewAction = NewObject<UBDLAction>(this, ActionClass);
	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
		if(NewAction->bAutoStart&&ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}
	}
	
}

void UBDLActionComponent::RemoveAction(UBDLAction* ActionToRemove)
{
	// Instantiate the class and add it to our action array
	if(!ensure(ActionToRemove && !ActionToRemove->GetIsRunning()))
	{
		return;
	}
	Actions.Remove(ActionToRemove);
}

void UBDLActionComponent::ServerStartAction_Implementation(AActor* Instigator, FName ActionName)
{
	StartActionByName(Instigator, ActionName);
}

void UBDLActionComponent::ServerStopAction_Implementation(AActor* Instigator, FName ActionName)
{
	StopActionByName(Instigator, ActionName);
}

bool UBDLActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for(UBDLAction* Action: Actions)
	{
		if(Action && Action->ActionName == ActionName)
		{
			if(!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				continue;
			}
			if(!GetOwner()->HasAuthority())
			{
				ServerStartAction(Instigator, ActionName);
			}
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
			if(Action->GetIsRunning())
			{
				 if(!GetOwner()->HasAuthority())
				 {
					 ServerStopAction(Instigator, ActionName);
				 }
				 Action->StopAction(Instigator);
				 return true;
			}
		}
	}
	return false;
}

UBDLAction* UBDLActionComponent::GetAction(TSubclassOf<UBDLAction> ActionClass) const
{
	for (UBDLAction* Action : Actions)
	{
		if (Action && Action->IsA(ActionClass))
		{
			return Action;
		}
	}

	return nullptr;
}

void UBDLActionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UBDLActionComponent, Actions);
}

bool UBDLActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for(UBDLAction* Action: Actions){
		if(Action)
		{
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
		}
	}
	return WroteSomething;
}
