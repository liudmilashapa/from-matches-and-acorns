// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraFightUtility.generated.h"

UCLASS()
class LUTEST_2_API ACameraFightUtility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraFightUtility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
      AActor * Camera1;

    UPROPERTY(EditAnywhere)
        AActor * Camera2;

   void changeCamera();
};
