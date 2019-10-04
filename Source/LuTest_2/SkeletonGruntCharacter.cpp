// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonGruntCharacter.h"

// Sets default values
ASkeletonGruntCharacter::ASkeletonGruntCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkeletonGruntCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkeletonGruntCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkeletonGruntCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ASkeletonGruntCharacter::GetRangeOfDefeat()
{
    return RangeOfDefeat;
}

