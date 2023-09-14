// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLItemChest.h"

#include "Net/UnrealNetwork.h"

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
	bReplicates = true;
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
	//LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
	bLidOpened = !bLidOpened;
	OnRep_LidOpened();
}

void ABDLItemChest::OnRep_LidOpened()
{
	float CurPitch = bLidOpened ? TargetPitch : 0.0f;
	LidMesh->SetRelativeRotation(FRotator(CurPitch, 0, 0));
}

void ABDLItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABDLItemChest, bLidOpened);
}

