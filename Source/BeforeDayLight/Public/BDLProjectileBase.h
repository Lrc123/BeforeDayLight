// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BDLProjectileBase.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UCameraShakeBase;


USTRUCT(BlueprintType)
struct FProjectileSparseData 
{
	GENERATED_BODY()

	FProjectileSparseData(): ImpactShakeInnerRadius(0.f),ImpactShakeOuterRadius(1500.f){}

	UPROPERTY(EditDefaultsOnly, Category="Effects|Shake")
	float ImpactShakeInnerRadius;
	UPROPERTY(EditDefaultsOnly, Category="Effects|Shake")
	float ImpactShakeOuterRadius;
};


UCLASS(Abstract, SparseClassDataTypes=ProjectileSparseData)
class BEFOREDAYLIGHT_API ABDLProjectileBase : public AActor
{
	GENERATED_BODY()

	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	TSubclassOf<UCameraShakeBase> ImpactShake;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UParticleSystem* ImpactVFX;

	UPROPERTY(EditDefaultsOnly, Category="Sounds")
	USoundBase* ExplodeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config", meta=(AllowPrivateAccess = "true"))
	float ForceStrength = 250.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config", meta=(AllowPrivateAccess = "true"))
	float LifeSpan = 4.5f;

	FTimerHandle  TimeHandle_DestroySelf;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void DestroySelf_TimeElapsed();

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();
	
public:
	ABDLProjectileBase();

	virtual void BeginPlay() override;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	float ImpactShakeInnerRadius_DEPRECATED;
	UPROPERTY()
	float ImpactShakeOuterRadius_DEPRECATED;

#endif
	
#if WITH_EDITOR
public:
	virtual void MoveDataToSparseClassDataStruct() const override;

#endif

};
