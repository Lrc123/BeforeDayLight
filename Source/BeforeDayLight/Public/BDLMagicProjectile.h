// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLProjectileBase.h"
#include "GameplayTagContainer.h"
#include "BDLMagicProjectile.generated.h"

class UBDLActionEffect;

UCLASS()
class BEFOREDAYLIGHT_API ABDLMagicProjectile : public ABDLProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABDLMagicProjectile();

	void PostInitializeComponents() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DamageAmount = 10.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UBDLActionEffect> BurningActionClass;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override; 
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
