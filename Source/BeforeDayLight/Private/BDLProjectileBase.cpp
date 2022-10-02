// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLProjectileBase.h"

#include "BDLCharacter.h"
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

void ABDLProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if(!OtherActor->IsA(ABDLCharacter::StaticClass()))
	if(OtherActor && OtherActor != GetInstigator())
	{
		Explode();
	}
}

void ABDLProjectileBase::Explode_Implementation()
{
	if(ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		EffectComp->DeactivateSystem();
		MovementComp->StopMovementImmediately();
		SetActorEnableCollision(false);
		
		Destroy();
	}
}




void ABDLProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}



// Called every frame
void ABDLProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

