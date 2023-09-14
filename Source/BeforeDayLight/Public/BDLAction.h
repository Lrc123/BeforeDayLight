// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "BDLAction.generated.h"

class UWorld;
class UBDLActionComponent;

// using a struct can make sure the data would be arrived at the same time
USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	bool bIsRunning;
	
	UPROPERTY()
	AActor* Instigator;
};

/**
 * 
 */
// you need blueprintable to make child class or bp of this
UCLASS(Blueprintable)
class BEFOREDAYLIGHT_API UBDLAction : public UObject
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category="Action")
	UBDLActionComponent* GetOwningComponent() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer BlockTags;

	UPROPERTY(ReplicatedUsing="OnRep_RepData")
	FActionRepData RepData;
	//bool bIsRunning;

	UFUNCTION()
	void OnRep_RepData();
	//UFUNCTION()
	//void OnRep_IsRunning();
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Action")
	bool bAutoStart;

	UFUNCTION(BlueprintCallable, Category="Action")
	bool GetIsRunning();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);

	/*use Fname to refer via name instead of using hard reference*/
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;

	virtual UWorld* GetWorld() const override;

	bool IsSupportedForNetworking() const override
	{
		return true;
	}
};


