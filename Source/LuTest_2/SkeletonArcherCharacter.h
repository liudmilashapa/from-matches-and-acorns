// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkeletonArcherCharacter.generated.h"

class CharacterInfo;
enum class EArcherAnimationState : uint8;

UCLASS()
class LUTEST_2_API ASkeletonArcherCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkeletonArcherCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        int RangeOfDefeat = 3;

    int GetRangeOfDefeat();

    CharacterInfo * GetCharacterInfo();

private:

    CharacterInfo * m_pArcherCharacterInfo;

//    ChangeAnimationState();

  //   EArcherAnimationState  * m_curentAnimationState;
};
