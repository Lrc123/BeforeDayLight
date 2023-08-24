// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLAttributeComponent.h"
#include "GameFramework/Actor.h"
#include "BDLExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class BEFOREDAYLIGHT_API ABDLExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABDLExplosiveBarrel();
	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Explosives", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MeshComp;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Explosives", meta=(AllowPrivateAccess="true"))
	URadialForceComponent* RadialForceComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBDLAttributeComponent* AttributeComp;

	FTimerHandle DestroyTimerHandle;

	UFUNCTION(BlueprintCallable)
	void DestroyActorWithDelay();

	UFUNCTION(BlueprintCallable)
	void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
	float DelayTime = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
	float ExplodeDmg = 10.f;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnHealthChanged(AActor* InstigatorActor, UBDLAttributeComponent* OwningComp, float NewHealth, float Delta);

	UFUNCTION(BlueprintCallable)
	void Explode();
	
};
