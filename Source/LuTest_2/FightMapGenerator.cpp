// Fill out your copyright notice in the Description page of Project Settings.


#include "FightMapGenerator.h"

#include "Engine/World.h"
#include "SkeletonArcherCharacter.h"

// Sets default values
AFightMapGenerator::AFightMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFightMapGenerator::BeginPlay()
{
	Super::BeginPlay();
    GenerateMainCharacter();
}

// Called every frame
void AFightMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFightMapGenerator::GenerateMainCharacter()
{
    if (BP_ArcherCharacter)
    {
        FActorSpawnParameters spawnParams;
//        spawnParams.Template = Cast<AActor>(*BP_ArcherCharacter);

        // FTransform transform = GetTransform();
        // transform.SetLocation(_hexActor.GetActorTransform().GetLocation());

        FTransform transform = GetTransform();

        transform.SetLocation(FVector(-4086, -9561, 470));
        ASkeletonArcherCharacter * actor = GetWorld()->SpawnActor<ASkeletonArcherCharacter>(BP_ArcherCharacter, transform, spawnParams);
        m_SkeletonArcherCharacter.Add(actor);
    }
}
