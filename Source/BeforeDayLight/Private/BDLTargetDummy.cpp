// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLTargetDummy.h"

#include <string>

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White,String)

// Sets default values
ABDLTargetDummy::ABDLTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UBDLAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &ABDLTargetDummy::OnHealthChanged);

}

// Called when the game starts or when spawned
void ABDLTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABDLTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABDLTargetDummy::OnHealthChanged(AActor* InstigatorActor, UBDLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if(Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

