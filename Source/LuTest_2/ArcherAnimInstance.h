// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ArcherAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EArcherAnimationState  : uint8
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
class LUTEST_2_API UArcherAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Enum)
        EArcherAnimationState ArcherAnimationState = EArcherAnimationState::Idle;
};
