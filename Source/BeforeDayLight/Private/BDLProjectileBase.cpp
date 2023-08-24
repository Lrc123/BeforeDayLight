// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLProjectileBase.h"

#include "BDLCharacter.h"
#include "AI/BDLAIController.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABDLProjectileBase::ABDLProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ABDLProjectileBase::OnActorHit);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->InitialSpeed = 3000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;



}

void ABDLProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeHandle_DestroySelf, this, &ABDLProjectileBase::DestroySelf_TimeElapsed, LifeSpan);
}

void ABDLProjectileBase::DestroySelf_TimeElapsed()
{
	Destroy();
}


void ABDLProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if(!OtherActor->IsA(ABDLCharacter::StaticClass()))
	UBDLAttributeComponent* AttributeComp = Cast<UBDLAttributeComponent>(OtherActor->GetComponentByClass(UBDLAttributeComponent::StaticClass()));
	if(OtherActor
		&& OtherActor != GetInstigator()
		&& !AttributeComp)
	{
		Explode();
	}
}

void ABDLProjectileBase::Explode_Implementation()
{
	if(ensure(IsValid(this)))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		EffectComp->DeactivateSystem();
		MovementComp->StopMovementImmediately();
		SetActorEnableCollision(false);
		UGameplayStatics::PlaySoundAtLocation(this, ExplodeSound, GetActorLocation(),GetActorRotation());
		UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, GetActorLocation(), GetImpactShakeInnerRadius(), GetImpactShakeOuterRadius());
		Destroy();
	}
}


void ABDLProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

#if WITH_EDITOR
void ABDLProjectileBase::MoveDataToSparseClassDataStruct() const
{
	const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
	if(BPClass == nullptr || BPClass->bIsSparseClassDataSerializable == true)
	{
		return;
	}
	Super::MoveDataToSparseClassDataStruct();
#if WITH_EDITORONLY_DATA
	FProjectileSparseData* SparseClassData = GetProjectileSparseData();

	SparseClassData->ImpactShakeInnerRadius = ImpactShakeInnerRadius_DEPRECATED;
	SparseClassData->ImpactShakeOuterRadius = ImpactShakeOuterRadius_DEPRECATED;

#endif
}

#endif



