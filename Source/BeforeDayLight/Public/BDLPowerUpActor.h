// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BDLGamePlayInterface.h"
#include "Components/SphereComponent.h"
#include "BDLPowerUpActor.generated.h"

UCLASS()
class BEFOREDAYLIGHT_API ABDLPowerUpActor : public AActor, public IBDLGamePlayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABDLPowerUpActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bIsActive;

	UPROPERTY(EditAnywhere, Category="Powerup")
	float RespawnTime;

	FTimerHandle TimerHandle_RespawnTimer;

	UFUNCTION()
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerupState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

};
