// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BDLAction.generated.h"

class UWorld;

/**
 * 
 */
// you need blueprintable to make child class or bp of this
UCLASS(Blueprintable)
class BEFOREDAYLIGHT_API UBDLAction : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);
	
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);

	/*use Fname to refer via name instead of using hard reference*/
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;

	UWorld* GetWorld() const override;
};


