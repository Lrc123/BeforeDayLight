// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	void PostInitializeComponents();

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Explosives", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MeshComp;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Explosives", meta=(AllowPrivateAccess="true"))
	URadialForceComponent* RadialForceComp;


	UFUNCTION(BlueprintCallable)
	void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
