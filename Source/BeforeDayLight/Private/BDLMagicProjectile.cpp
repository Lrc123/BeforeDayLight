// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLMagicProjectile.h"

#include "BDLActionComponent.h"
#include "BDLGameplayFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BDLActionEffect.h"


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
		UE_LOG(LogTemp, Log, TEXT("Instigator is : %s"), *GetNameSafe(GetInstigator()));
		
		/*
		UBDLAttributeComponent* AttributeComp = Cast<UBDLAttributeComponent>(OtherActor->GetComponentByClass(UBDLAttributeComponent::StaticClass()));
		if (AttributeComp && AttributeComp->IsAlive())
		{
			Explode();
			AttributeComp->ApplyHealthChange(GetInstigator(), -DamageAmount);
			Destroy();
		}
		*/
		UBDLActionComponent* ActionComp = Cast<UBDLActionComponent>(OtherActor->GetComponentByClass(UBDLActionComponent::StaticClass()));
		if(ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			MovementComp->Velocity = -MovementComp->Velocity;
			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}
		if(UBDLGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			Explode();
			//Destroy();
			if(ActionComp && HasAuthority())
			{
				ActionComp->AddAction(GetInstigator(), BurningActionClass);
			}
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

