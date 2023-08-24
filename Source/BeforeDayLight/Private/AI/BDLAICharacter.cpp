// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BDLAICharacter.h"

#include "BDLWorldUserWidget.h"
#include "BrainComponent.h"
#include "AI/BDLAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Perception/PawnSensingComponent.h"


#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White,String)

// Sets default values
ABDLAICharacter::ABDLAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	AttributeComp = CreateDefaultSubobject<UBDLAttributeComponent>("AttributeComp");
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	TimeToHitParamName = "TimeToHit";
}



void ABDLAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &ABDLAICharacter::OnHealthChanged);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ABDLAICharacter::OnPawnSeen);
}

void ABDLAICharacter::OnHealthChanged(AActor* InstigatorActor, UBDLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if(Delta < 0.0f)
	{
		if(InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}
		if(ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<UBDLWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
			if(ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}
		

		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
		
		if(NewHealth <= 0.0f)
		{
			ABDLAIController* AIC = Cast<ABDLAIController>(GetController());
			if(ensure(AIC))
			{
				 // stop bt
				AIC->GetBrainComponent()->StopLogic("Killed");
			}
			// ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			// set lifespan
			SetLifeSpan(10.0f);
		}
	}
}

void ABDLAICharacter::DestroySelf_TimeElapsed()
{
	Destroy();
}


void ABDLAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}

void ABDLAICharacter::SetTargetActor(AActor* NewTarget)
{
	ABDLAIController* AIC = Cast<ABDLAIController>(GetController());
	if(AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject("TargetActor", NewTarget);
	}
	
}



