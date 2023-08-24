// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLMagicProjectile.h"

#include "BDLAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABDLMagicProjectile::ABDLMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SphereComp->OnComponentHit.RemoveDynamic(this, &ABDLMagicProjectile::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABDLMagicProjectile::OnActorOverlap);

	
}

void ABDLMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	/*
	if(OtherActor && OtherActor != GetInstigator())
	{
		UBDLAttributeComponent* AttributeComp = Cast<UBDLAttributeComponent>(OtherActor->GetComponentByClass(UBDLAttributeComponent::StaticClass()));
		
		if (AttributeComp)
		{
			Explode();
			AttributeComp->ApplyHealthChange(-DamageAmount);
			Destroy();
		}
	}
	*/
}



void ABDLMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		UBDLAttributeComponent* AttributeComp = Cast<UBDLAttributeComponent>(OtherActor->GetComponentByClass(UBDLAttributeComponent::StaticClass()));
		
		if (AttributeComp && AttributeComp->IsAlive())
		{
			Explode();
			AttributeComp->ApplyHealthChange(GetInstigator(), -DamageAmount);
			Destroy();
		}
	}
}




void ABDLMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}



// Called every frame
void ABDLMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

