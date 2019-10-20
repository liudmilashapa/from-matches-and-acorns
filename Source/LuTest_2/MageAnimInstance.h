// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MageAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMageAnimationState : uint8
{
    Idle,
    Jump,
    Hit,
    Spawn,
    Death,
    Shooting,
    RandomShooting,
    Run
};


/**
 * 
 */
UCLASS()
class LUTEST_2_API UMageAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Enum)
        EMageAnimationState MageAnimationState = EMageAnimationState::Idle;
};
