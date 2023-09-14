// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BDLAICharacter.h"

#include "BDLWorldUserWidget.h"
#include "BrainComponent.h"
#include "../../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/StatTimer.h"
#include "AI/BDLAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"


#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White,String)

// Sets default values
ABDLAICharacter::ABDLAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	AttributeComp = CreateDefaultSubobject<UBDLAttributeComponent>("AttributeComp");
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	//GetMesh()->SetGenerateOverlapEvents(true);

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
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();
			// set lifespan
			SetLifeSpan(10.0f);
		}
	}
	
	//DrawDebugString(GetWorld(), GetActorLocation(), "Health Changed", nullptr, FColor::White, 4.0f, true);

	bool IsLowHealth = AttributeComp->GetCurHealth() / AttributeComp->GetMaxHealth() < 0.5f;
	ABDLAIController* AIC = Cast<ABDLAIController>(GetController());
	if(AIC)
	{
		 UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		 BBComp->SetValueAsBool("IsLowHealth", IsLowHealth);
	}
}

void ABDLAICharacter::DestroySelf_TimeElapsed()
{
	Destroy();
}

void ABDLAICharacter::LostTarget()
{
	SetTargetActor(nullptr);
}


void ABDLAICharacter::OnPawnSeen(APawn* Pawn)
{
	if(GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);
	}
	UBDLWorldUserWidget* NewWidget = CreateWidget<UBDLWorldUserWidget>(GetWorld(), SpottedWidgetClass);
	if (NewWidget)
	{
		NewWidget->AttachedActor = this;
		// Index of 10 (or anything higher than default of 0) places this on top of any other widget.
		// May end up behind the minion health bar otherwise.
		NewWidget->AddToViewport(10);
	}
	GetWorldTimerManager().SetTimer(TimerHandle_LostTarget, this, &ABDLAICharacter::LostTarget ,5);
	//DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}

void ABDLAICharacter::SetTargetActor(AActor* NewTarget)
{
	ABDLAIController* AIC = Cast<ABDLAIController>(GetController());
	if(AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject("TargetActorKey", NewTarget);
	}
	
}

AActor* ABDLAICharacter::GetTargetActor() const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorKey));
	}

	return nullptr;
}

