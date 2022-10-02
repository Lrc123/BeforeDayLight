// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLProjectileBase.h"
#include "BDLDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class BEFOREDAYLIGHT_API ABDLDashProjectile : public ABDLProjectileBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Teleport")
	float TeleportDelay = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, Category="Teleport")
	float DetonateDelay = 0.2f;

	// Handle to cancel timer if hit something
	FTimerHandle TimerHandle_DelayedDetonate;

	// Base Class using BlueprintNativeEvent must override using _Implementation
	virtual void Explode_Implementation() override;


	virtual void BeginPlay() override;


public:
	ABDLDashProjectile();

	UFUNCTION()	
	bool GetIsTeleporting();
	
	UFUNCTION()	
	void TeleportInstigator();
	
};
