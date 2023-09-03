// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLInteractionComponent.h"
#include "BDLGamePlayInterface.h"
#include "DrawDebugHelpers.h"
#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White,String)

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(
	TEXT("bdl.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

// Sets default values for this component's properties
UBDLInteractionComponent::UBDLInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBDLInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UBDLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBDLInteractionComponent::PrimaryInteract()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();


	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	/*
	FHitResult Hit;
	 GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	*/

	TArray<FHitResult> Hits;

	float Radius = 30.f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams,
	                                                       Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		if (bDebugDraw)
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UBDLGamePlayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IBDLGamePlayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
	}

	if (bDebugDraw)
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}
