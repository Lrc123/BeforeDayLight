// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLGameplayFunctionLibrary.h"

#include "BDLAttributeComponent.h"


bool UBDLGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	UBDLAttributeComponent* AttributeComp = UBDLAttributeComponent::GetAttributes(TargetActor);
	if(AttributeComp)
	{
		return AttributeComp->ApplyHealthChange(DamageCauser, -DamageAmount);
	}
	return false;
}

bool UBDLGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	if(ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if(HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			FVector ImpulseDirection = HitResult.TraceEnd - HitResult.TraceStart;
			ImpulseDirection.Normalize();
			HitComp->AddImpulseAtLocation(ImpulseDirection * 300000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}
		return true;
	}
	return false;
}


