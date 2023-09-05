// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "BDLAction.generated.h"

class UWorld;
class UBDLActionComponent;

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

	bool bIsRunning;
	
public:

	UFUNCTION(BlueprintCallable, Category="Action")
	bool GetIsRunning();
	
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);
	
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);

	/*use Fname to refer via name instead of using hard reference*/
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;

	virtual UWorld* GetWorld() const override;
};


