// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"


void UBDLWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(!IsValid(AttachedActor))
	{
		RemoveFromParent();
		UE_LOG(LogTemp, Log, TEXT("AttachedActor is no longer valid, removing Health Widget"));
		return;
	}

	FVector2d ScreenPosition;
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition))
	{
		float Scale =UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPosition /= Scale;

		if(ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
	
}

