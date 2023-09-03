// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLAttributeComponent.h"
#include "BDLWorldUserWidget.h"
#include "GameFramework/Character.h"
#include "BDLAICharacter.generated.h"

class UPawnSensingComponent;
class UBDLWorldUserWidget;
class UUserWidget;

UCLASS()
class BEFOREDAYLIGHT_API ABDLAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABDLAICharacter();
	void PostInitializeComponents();

protected:

	UBDLWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	FTimerHandle TimerHandle_DestroySelf;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBDLAttributeComponent* AttributeComp;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	/* VisibleAnywhere = read-only, still useful to view in-editor and enforce a convention. */
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UBDLAttributeComponent* OwningComp, float NewHealth, float Delta);

	UFUNCTION()
	void DestroySelf_TimeElapsed();

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void SetTargetActor(AActor* NewTarget);


private:
	FTimerHandle TimerHandle_LostTarget;
	UFUNCTION()
	void LostTarget();

};
