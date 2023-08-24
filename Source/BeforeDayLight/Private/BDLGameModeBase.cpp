// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLGameModeBase.h"

#include "EngineUtils.h"
#include "AI/BDLAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"


void ABDLGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ABDLGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ABDLGameModeBase::SpawnBotTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance =  UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ABDLGameModeBase::OnQueryCompleted);
}

void ABDLGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	
	int32 NrOfAliveBots = 0;
	for(TActorIterator<ABDLAICharacter> It(GetWorld()); It; ++It)
	{
		ABDLAICharacter* Bot = *It;
		//UBDLAttributeComponent* AttributeComp = Cast<UBDLAttributeComponent>(Bot->GetComponentByClass(UBDLAttributeComponent::StaticClass()));
		UBDLAttributeComponent* AttributeComp = UBDLAttributeComponent::GetAttributes(Bot);
		if(ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	float MaxBotCount = 10.0f;
	if(DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	if(NrOfAliveBots >= MaxBotCount)
	{
		return;
	}
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed"));
		return ;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if(Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}


ABDLGameModeBase::ABDLGameModeBase()
{
	SpawnTimerInterval = 3.f;
}

