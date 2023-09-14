// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLCharacter.h"
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
	
	virtual void StartPlay() override;
	
	UFUNCTION()
	void OnActorKilled(AActor* VictimActor, AActor* Killer);
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="AI");
	UEnvQuery* SpawnBotQuery;
	
	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	int32 CreditsPerKill;

	UPROPERTY(EditDefaultsOnly, Category="Powerups")
	UEnvQuery* PowerupSpawnQuery;
	
	UPROPERTY(EditDefaultsOnly, Category="Powerups")
	TArray<TSubclassOf<AActor>> PowerupClasses;

	UPROPERTY(EditDefaultsOnly, Category="Powerups")
	float RequiredPowerupDistance;

	UPROPERTY(EditDefaultsOnly, Category="Powerups")
	int32 DesiredPowerupCount;
	

	UFUNCTION()
	void SpawnBotTimerElapsed();
	
	UFUNCTION()
	void OnBotSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnPowerupSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* DifficultyCurve;

	UFUNCTION(Exec)
	void KillAllAI();

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	
};
