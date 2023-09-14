// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLPlayerController.h"


void ABDLPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}
