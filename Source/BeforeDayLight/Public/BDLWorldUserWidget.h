// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "BDLWorldUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class BEFOREDAYLIGHT_API UBDLWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
public:
	UPROPERTY(BlueprintReadOnly, Category="UI")
	AActor* AttachedActor;

	UPROPERTY(BlueprintReadOnly, Category="UI")
	FVector WorldOffset;
};
