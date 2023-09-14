// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLAction.h"
#include "BDLActionComponent.h"
#include "BeforeDayLight/BeforeDayLight.h"
#include "Net/UnrealNetwork.h"

bool UBDLAction::CanStart_Implementation(AActor* Instigator)
{
	if(GetIsRunning()){
		return false;
	}
	UBDLActionComponent* Comp = GetOwningComponent();
	if(Comp->ActiveGameplayTags.HasAny(BlockTags)){
		return false;
	}
	return true;
}

void UBDLAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);
	UBDLActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);
	RepData.bIsRunning = true;
	RepData.Instigator = Instigator;
}

// could be override in blueprint so move the condition outside
void UBDLAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Stopped: %s"), *ActionName.ToString()), FColor::White);
	//ensureAlways(bIsRunning);
	UBDLActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	RepData.bIsRunning = false;
	RepData.Instigator = Instigator;
}


bool UBDLAction::GetIsRunning()
{
	return RepData.bIsRunning;
}

void UBDLAction::OnRep_RepData()
{
	if(RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}else
	{
		StopAction(RepData.Instigator);
	}
}

UBDLActionComponent* UBDLAction::GetOwningComponent() const
{
	return Cast<UBDLActionComponent>(GetOuter());
}

UWorld* UBDLAction::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if(Comp)
	{
		return Comp->GetWorld();
	}
	return nullptr;
}

/**
 * @brief 
 * @param OutLifetimeProps
 * The GetLifetimeReplicatedProps function is an important part of Unreal Engine's network replication system. It is called to define which properties of an object should be replicated over the network. By adding bIsRunning to the list of replicated properties, you're telling Unreal Engine to keep this property in sync across the network for instances of UBDLAction.
 */
void UBDLAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(UBDLAction, bIsRunning); //  this specify that bIsRunning should be replicated and once it is changed all connected clients will update this value
	DOREPLIFETIME(UBDLAction, RepData);
}

