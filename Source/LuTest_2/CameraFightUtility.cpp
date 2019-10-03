// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraFightUtility.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraFightUtility::ACameraFightUtility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraFightUtility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraFightUtility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACameraFightUtility::changeCamera()
{
    APlayerController * playerController = UGameplayStatics::GetPlayerController(this, 0);
    if (playerController)
    { 
        if (Camera1 && playerController->GetViewTarget() == Camera1) 
        {
            playerController->SetViewTargetWithBlend(Camera2);
        }
        else if (Camera2)
        {
            playerController->SetViewTargetWithBlend(Camera1);
        }
    }
}
