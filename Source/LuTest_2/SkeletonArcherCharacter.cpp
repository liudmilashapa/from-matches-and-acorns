// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonArcherCharacter.h"

#include "CharacterInfo.h"
#include "ArcherAnimInstance.h"

// Sets default values
ASkeletonArcherCharacter::ASkeletonArcherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    m_pArcherCharacterInfo = new CharacterInfo(10, 3, 4);
}

// Called when the game starts or when spawned
void ASkeletonArcherCharacter::BeginPlay()
{
	Super::BeginPlay();

  //  *m_curentAnimationState = EArcherAnimationState::Idle;
}

// Called every frame
void ASkeletonArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkeletonArcherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


int ASkeletonArcherCharacter::GetRangeOfDefeat()
{
    return RangeOfDefeat;
}

CharacterInfo * ASkeletonArcherCharacter::GetCharacterInfo()
{
    return m_pArcherCharacterInfo;
}