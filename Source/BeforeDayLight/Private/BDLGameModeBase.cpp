// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLGameModeBase.h"

#include "BDLCharacter.h"
#include "EngineUtils.h"
#include "AI/BDLAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"


static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("bdl.SpawnBots"), true, TEXT("Enable spawning of bots via timer"), ECVF_Cheat);

void ABDLGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ABDLGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ABDLGameModeBase::SpawnBotTimerElapsed()
{
	if(!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot Spawning disabled via cvar 'CVarSpawnBots' "));
		return;
	}
	UEnvQueryInstanceBlueprintWrapper* QueryInstance =  UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ABDLGameModeBase::OnQueryCompleted);
}

void ABDLGameModeBase::KillAllAI()
{
	for(TActorIterator<ABDLAICharacter> It(GetWorld()); It; ++It)
	{
		ABDLAICharacter* Bot = *It;
		//UBDLAttributeComponent* AttributeComp = Cast<UBDLAttributeComponent>(Bot->GetComponentByClass(UBDLAttributeComponent::StaticClass()));
		UBDLAttributeComponent* AttributeComp = UBDLAttributeComponent::GetAttributes(Bot);
		if(ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			AttributeComp->Kill(this); // @fixme: pass in player for kill credit
		}
	}
	
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

void ABDLGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if(ensure(Controller))
	{
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}


void ABDLGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	ABDLCharacter* Player = Cast<ABDLCharacter>(VictimActor);
	if(Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());
		float RespawnDelay = 2.f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}

	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));
}

ABDLGameModeBase::ABDLGameModeBase()
{
	SpawnTimerInterval = 3.f;
}

