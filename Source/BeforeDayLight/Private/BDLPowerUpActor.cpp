// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLPowerUpActor.h"

// Sets default values
ABDLPowerUpActor::ABDLPowerUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(SphereComp);

	RespawnTime = 8.0f;

	bIsActive = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABDLPowerUpActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABDLPowerUpActor::ShowPowerup()
{
	SetPowerupState(true);
}

void ABDLPowerUpActor::SetPowerupState(bool bNewIsActive)
{
	bIsActive = bNewIsActive;
	RootComponent->SetVisibility(bIsActive, true);
}

void ABDLPowerUpActor::HideAndCooldownPowerup()
{
	SetPowerupState(false);
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ABDLPowerUpActor::ShowPowerup, RespawnTime);
}


void ABDLPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{
	
}






