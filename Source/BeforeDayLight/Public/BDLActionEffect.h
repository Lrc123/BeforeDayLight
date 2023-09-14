// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLAction.h"
#include "BDLActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class BEFOREDAYLIGHT_API UBDLActionEffect : public UBDLAction
{
	GENERATED_BODY()
	
public:
	UBDLActionEffect();
	
	void StartAction_Implementation(AActor* Instigator) override;
	void StopAction_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect");
	float Duration;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect");
	float Period;

	FTimerHandle DurationHandle;
	FTimerHandle PeriodHandle;
	

	UFUNCTION(BlueprintNativeEvent, Category="Effect")
	void ExecutePeriodicEffect(AActor* Instigator);

};
