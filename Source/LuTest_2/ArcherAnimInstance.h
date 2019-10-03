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
    Death,
    Shooting
};

/**
 * 
 */
UCLASS()
class LUTEST_2_API UArcherAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	


protected:
    /*True means that we're currently in air - or falling*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        bool bIsFalling;

    /*Holds the current speed of our character*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float MovementSpeed;

    /*Updates the above properties*/
    UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
        void UpdateAnimationProperties();

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
        EArcherAnimationState ArcherAnimationState;
};
