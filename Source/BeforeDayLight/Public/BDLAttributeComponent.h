// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BDLAttributeComponent.generated.h"


//DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UBDLAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

// Alternative: Share the same signature with generic names
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, UBDLAttributeComponent*, OwningComp, float, NewValue, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEFOREDAYLIGHT_API UBDLAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Replicated, Category="Attributes")
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Replicated, Category="Attributes")
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,  Category="Attributes")
	float Rage = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category="Attributes")
	float MaxRage = 100.f;
	
	UPROPERTY(EditDefaultsOnly,  Category="Attributes")
	float DmgToRageFactor = 0.2f;
	
	UFUNCTION(NetMulticast, Reliable) //@TODO: mark as unreliable once we moved the 'state' out of BDLCharacter
	void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);

public:
	// Sets default values for this component's properties
	UBDLAttributeComponent();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static UBDLAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsFullHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetCurHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static bool IsActorAlive(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetCurRage() const;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxRage() const;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetDmgToRageFactor() const;
	UPROPERTY(BlueprintAssignable, Category="Delegates")
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnRageChanged;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyRageChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable)
	bool IsAlive();

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);
	
};

