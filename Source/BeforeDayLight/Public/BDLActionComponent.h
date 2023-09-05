// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "BDLActionComponent.generated.h"

class UBDLAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BEFOREDAYLIGHT_API UBDLActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddAction(TSubclassOf<UBDLAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	UBDLActionComponent();

protected:
	UPROPERTY()
	TArray<UBDLAction*> Actions;

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<UBDLAction>> DefaultActions;
	
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
