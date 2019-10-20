// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkeletonMageCharacter.generated.h"

class CharacterInfo;

UCLASS()
class LUTEST_2_API ASkeletonMageCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkeletonMageCharacter();

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

    CharacterInfo * m_pMageCharacterInfo;

};
