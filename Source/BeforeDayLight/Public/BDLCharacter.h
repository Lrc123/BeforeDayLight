// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLAttributeComponent.h"
#include "BDLDashProjectile.h"
#include "GameFramework/Character.h"
#include "BDLCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBDLInteractionComponent;
class UAnimMontage;
class ABDLDashProjectile;


UCLASS()
class BEFOREDAYLIGHT_API ABDLCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category= "Ability")
	TSubclassOf<AActor> BlackHoleProjectileClass;
	
	UPROPERTY(EditAnywhere, Category= "Ability")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBDLAttributeComponent* AttributeComp;


	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Dash;
	FTimerHandle TimerHandle_Rotating;
	float AttackAnimDelay = 0.2f;


public:
	// Sets default values for this character's properties
	ABDLCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UBDLInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere)
	ABDLDashProjectile* DashProjectile;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void AbilityUlt();
	void AbilityUlt_TimeElapsed();

	void Rotating_TimeElapsed();

	void Dash();
	void Dash_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	void CheckJump();

	void PrimaryInteract();

	UPROPERTY()
	bool jumping;

	
	UPROPERTY()
	bool rotating;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UBDLAttributeComponent* OwningComp, float NewHealth, float Delta);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

};
