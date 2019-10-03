// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrier_1.h"

// Sets default values
ABarrier_1::ABarrier_1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Mesh_1 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_1");
 //   Mesh_2 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_2");
 //   Mesh_3 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh_3");
 //   RootComponent = Mesh_1;
}

// Called when the game starts or when spawned
void ABarrier_1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarrier_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

