// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BDLWorldUserWidget.h"
#include "Components/ActorComponent.h"
#include "BDLInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEFOREDAYLIGHT_API UBDLInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	void PrimaryInteract();
	// Sets default values for this component's properties
	UBDLInteractionComponent();

protected:

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InFocus);

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category="Trace")
	float TraceDistance;
	
	UPROPERTY(EditDefaultsOnly, Category="Trace")
	float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category="Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UBDLWorldUserWidget> DefaultWidgetClass;
	
	UPROPERTY()
	UBDLWorldUserWidget* DefaultWidgetInstance;
	
	void FindBestInteractable();
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
