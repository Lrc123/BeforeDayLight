// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLPlayerState.h"


void ABDLPlayerState::AddCredits(int32 Delta)
{
	if(!ensure(Delta > 0.0f))
	{
		return;
	}
	Credits += Delta;
	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

bool ABDLPlayerState::RemoveCredits(int32 Delta)
{
	if(!ensure(Delta > 0.0f))
	{
		return false;
	}
	if(Credits < Delta)
	{
		return false;
	}
	Credits -= Delta;
	OnCreditsChanged.Broadcast(this, Credits, -Delta);
	return true;
}

