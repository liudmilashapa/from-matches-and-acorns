// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherAnimInstance.h"

void UArcherAnimInstance::UpdateAnimationProperties()
{
    //Get the pawn which is affected by our anim instance
    AActor* Pawn = GetOwningActor();

    if (Pawn)
    {
        //Update our falling property


        //Update our movement speed
        MovementSpeed = Pawn->GetVelocity().Size();
    }
}