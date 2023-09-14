// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "BDLActionComponent.generated.h"

class UBDLAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEFOREDAYLIGHT_API UBDLActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddAction(AActor* Instigator, TSubclassOf<UBDLAction> ActionClass);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	void RemoveAction(UBDLAction* ActionToRemove);

	/* Returns first occurance of action matching the class provided */
	UFUNCTION(BlueprintCallable, Category = "Actions")
	UBDLAction* GetAction(TSubclassOf<UBDLAction> ActionClass) const;

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	UBDLActionComponent();

protected:
	UPROPERTY(Replicated)
	TArray<UBDLAction*> Actions;

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<UBDLAction>> DefaultActions;

	UFUNCTION(Server, Reliable)
	void ServerStartAction(AActor* Instigator, FName ActionName);
	
	UFUNCTION(Server, Reliable)
	void ServerStopAction(AActor* Instigator, FName ActionName);
	
	virtual void BeginPlay() override;

public:
	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
