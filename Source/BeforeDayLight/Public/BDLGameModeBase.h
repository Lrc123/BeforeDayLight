// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "GameFramework/GameModeBase.h"
#include "BDLGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class BEFOREDAYLIGHT_API ABDLGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABDLGameModeBase();
	
	virtual  void StartPlay() override;
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="AI");
	UEnvQuery* SpawnBotQuery;
	
	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> MinionClass;

	UFUNCTION()
	void SpawnBotTimerElapsed();
	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* DifficultyCurve;
	
};
