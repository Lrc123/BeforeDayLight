// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLItemChest.h"

// Sets default values
ABDLItemChest::ABDLItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;

}

// Called when the game starts or when spawned
void ABDLItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABDLItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABDLItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	//throw std::logic_error("The method or operation is not implemented.");
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

