// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonMageCharacter.h"

// Sets default values
ASkeletonMageCharacter::ASkeletonMageCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkeletonMageCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkeletonMageCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkeletonMageCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ASkeletonMageCharacter::GetRangeOfDefeat()
{
    return RangeOfDefeat;
}

CharacterInfo * ASkeletonMageCharacter::GetCharacterInfo()
{
    return m_pMageCharacterInfo;
}
