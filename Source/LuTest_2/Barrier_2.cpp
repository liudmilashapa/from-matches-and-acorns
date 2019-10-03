// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrier_2.h"

// Sets default values
ABarrier_2::ABarrier_2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Mesh_1 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_1");
}

// Called when the game starts or when spawned
void ABarrier_2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarrier_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

