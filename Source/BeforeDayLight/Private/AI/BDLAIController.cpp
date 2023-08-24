// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BDLAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void ABDLAIController::BeginPlay()
{
	Super::BeginPlay();

	if(ensureMsgf(BehaviorTree, TEXT("Behavior Tree is nullptr! Please assign BehaviorTree in your AI Controller")))
	{
		RunBehaviorTree(BehaviorTree);
	}
	
	/*
	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if(MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("TargetLocation", MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
	*/
	
}




