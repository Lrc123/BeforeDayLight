// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLAction.h"
#include "BDLAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class BEFOREDAYLIGHT_API UBDLAction_ProjectileAttack : public UBDLAction
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;
	
	UPROPERTY(EditAnywhere, Category="Attack")
	float AttackAnimDelay = 0.2f;

	UPROPERTY(EditAnywhere, Category="Attack")
	UParticleSystem* CastingEffect;

	UPROPERTY(VisibleAnywhere, Category="Effects")
	FName HandSocketName;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

public:
	virtual void StartAction_Implementation(AActor* Instigator) override;

	UBDLAction_ProjectileAttack();
};
