// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GruntAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EGruntAnimationState : uint8
{
    Idle,
    Jump,
    Hit,
    Spawn,
    Death,
    Shooting,
    Run,
};
/**
 * 
 */
UCLASS()
class LUTEST_2_API UGruntAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Enum)
        EGruntAnimationState GruntAnimationState = EGruntAnimationState::Idle;
};
