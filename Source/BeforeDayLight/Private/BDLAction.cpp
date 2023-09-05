// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLAction.h"
#include "BDLActionComponent.h"

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
	UBDLActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRunning = true;
}

// could be override in blueprint so move the condition outside
void UBDLAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
	ensureAlways(bIsRunning);
	UBDLActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	bIsRunning = false;
}

bool UBDLAction::GetIsRunning()
{
	return bIsRunning;
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
