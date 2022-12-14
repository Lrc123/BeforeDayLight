// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "BDLMagicProjectile.h"
#include "BDLCharacter.h"
#include "DrawDebugHelpers.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White,String)

// Sets default values
ABDLExplosiveBarrel::ABDLExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;


	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(MeshComp);

	RadialForceComp->SetAutoActivate(false);

	// ignores 'Mass' of other objects
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->Radius = 2000.0f;
	RadialForceComp->ImpulseStrength = 1000.0f;
	RadialForceComp->DestructibleDamage = 500.0f;
	
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void ABDLExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//MeshComp->OnComponentHit.AddDynamic(this, &ABDLExplosiveBarrel::OnActorHit);
}


// Called every frame
void ABDLExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABDLExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*
	if (OtherActor->IsA(ABDLCharacter::StaticClass()))
	{
		PrintString(FString::Printf(TEXT("Hit: %s"), *OtherActor->GetName()));
		ABDLCharacter* player = Cast<ABDLCharacter>(OtherActor);
		//ABDLMagicProjectile* projectile = Cast<ABDLMagicProjectile>(OtherActor);
		FVector NewScale(0.3f, 0.3f, 0.3f);
		player->SetActorScale3D(NewScale);
		//projectile->SetActorScale3D(vec);
		RadialForceComp->FireImpulse();
	}

	UE_LOG(LogTemp, Log, TEXT("OnHit in Explosive Barrel"));
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	const FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	
	// https://unrealcommunity.wiki/logs-printing-messages-to-yourself-during-runtime-n5ifosqc
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
	*/

	//RadialForceComp->FireImpulse();

}


