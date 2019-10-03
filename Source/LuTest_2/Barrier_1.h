// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "Barrier_1.generated.h"

UCLASS()
class LUTEST_2_API ABarrier_1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrier_1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UStaticMeshComponent* Mesh_1;
 /*   UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UStaticMeshComponent* Mesh_2;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UStaticMeshComponent* Mesh_3;*/
};
