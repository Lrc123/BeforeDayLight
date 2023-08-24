// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BDLBTTask_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class BEFOREDAYLIGHT_API UBDLBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category="AI")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="AI")
	float MaxBulletSpread;

	UBDLBTTask_RangedAttack();
	
};
