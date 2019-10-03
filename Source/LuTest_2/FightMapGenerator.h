// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FightMapGenerator.generated.h"

class ASkeletonArcherCharacter;

UCLASS()
class LUTEST_2_API AFightMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFightMapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditDefaultsOnly, Category = "MapNodeActorCreate")
        TSubclassOf<ASkeletonArcherCharacter> BP_ArcherCharacter;

    void GenerateMainCharacter();

    TSet <ASkeletonArcherCharacter*> m_SkeletonArcherCharacter;

};
