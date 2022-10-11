// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLCharacter.h"

#include "BDLDashProjectile.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BDLInteractionComponent.h"
#include "Kismet/GameplayStatics.h"




#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White,String)

// Sets default values
ABDLCharacter::ABDLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UBDLInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<UBDLAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	jumping = false;
	rotating = false;
}

// Called when the game starts or when spawned
void ABDLCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABDLCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value);
}

void ABDLCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);
}

void ABDLCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ABDLCharacter::PrimaryAttack_TimeElapsed, AttackAnimDelay);

}

void ABDLCharacter::AbilityUlt()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ABDLCharacter::AbilityUlt_TimeElapsed, AttackAnimDelay);
}

void ABDLCharacter::Dash()
{
	if(DashProjectile && DashProjectile->GetIsTeleporting())
	{
		DashProjectile->TeleportInstigator();
	}else
	{
		PlayAnimMontage(AttackAnim);
		GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ABDLCharacter::Dash_TimeElapsed, AttackAnimDelay);
	}
}

void ABDLCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}



void ABDLCharacter::AbilityUlt_TimeElapsed()
{
	SpawnProjectile(BlackHoleProjectileClass);
}

void ABDLCharacter::Rotating_TimeElapsed()
{
	rotating = false;
}


void ABDLCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if(ensureAlways(ClassToSpawn))
	{
		
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;
		const float deltaYaw = abs(ControlRot.Yaw - GetActorRotation().Yaw);
		if(deltaYaw > 120)
		{
			rotating = true;
			GetWorldTimerManager().SetTimer(
				TimerHandle_Rotating, this, &ABDLCharacter::Rotating_TimeElapsed, 0.6f, false);
		}
		/*
		FQuat CurRotation = FQuat(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetControlRotation());
		FQuat CameraRotation = FQuat(CameraComp->GetComponentRotation());
		PrintString(CurRotation.ToString());
		PrintString(CameraRotation.ToString());
		if(!CurRotation.Equals(CurRotation))
		{
			
		}
		*/
		
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FHitResult Hit;
		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = TraceStart + (GetControlRotation().Vector() * 5000);

		FCollisionShape Shape;
		Shape.SetSphere(10.0f);

		// ignore player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		//ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FRotator ProjRotation;
		if(GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			ProjRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint - HandLocation).Rotator();
		}
		else
		{
			ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		}

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		if(ClassToSpawn == DashProjectileClass)
		{
			DashProjectile = Cast<ABDLDashProjectile>(GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams));
		}else
		{
			GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
		}
	}
	
}


void ABDLCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
	/*
	
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FHitResult Hit;
	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + CameraComp->GetComponentRotation().Vector() * 5000;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);


	// ignore player
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams, Params);

	//DrawDebugLine(GetWorld(), Start, Hit.ImpactPoint, FColor::Yellow, false, 2.0f, 0, 2.0f);
	//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10, 32, FColor::Cyan, false, 2.0f);

	//FRotator AimingRotator = bBlockingHit ? (Hit.ImpactPoint - HandLocation).Rotation() : (End - HandLocation).Rotation();
	FRotator AimingRotator = bBlockingHit ?
	FRotationMatrix::MakeFromX(Hit.ImpactPoint - HandLocation).Rotator()
	:FRotationMatrix::MakeFromX(End - HandLocation).Rotator();


	FTransform SpawnTM = FTransform(AimingRotator, HandLocation);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor::GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	*/
}

void ABDLCharacter::CheckJump() 
{
	if (jumping)
	{
		jumping = false;
	}
	else {
		jumping = true;
	}
}


void ABDLCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

// Called every frame
void ABDLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PrintString(rotating + "");
	
	if (jumping) 
	{
		Jump();
	}

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), ControlRot, 0.016f, 6.25f);
	
	if(rotating)
	{
		SetActorRotation(NewRotation);
	}



}

void ABDLCharacter::OnHealthChanged(AActor* InstigatorActor, UBDLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if(NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
	
}

void ABDLCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ABDLCharacter::OnHealthChanged);
}


// Called to bind functionality to input
void ABDLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABDLCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABDLCharacter::MoveRight);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ABDLCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Ability_Ult", IE_Pressed, this, &ABDLCharacter::AbilityUlt);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABDLCharacter::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABDLCharacter::CheckJump);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ABDLCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ABDLCharacter::Dash);

}


