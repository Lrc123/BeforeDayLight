// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLProjectileBase.h"
#include "BDLMagicProjectile.generated.h"



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

	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
