// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <set>

#include"HexActor.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MyMapGenerator.generated.h"

class ABarrier_1;
class ABarrier_2;
class ATree;
class Hex;
class AHexActor;
class ViewCoordinateGenerator;
class PathSearch;
class Grid;
class ASkeletonArcherCharacter;
enum StepAccessibility;

UCLASS()
class LUTEST_2_API AMyMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyMapGenerator();

    UPROPERTY(VisibleAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
        class UBoxComponent * SpawnPoint;

    UPROPERTY(EditDefaultsOnly, Category = "MapNodeActorCreate")
        TSubclassOf<AHexActor> BP_Hex;

    UPROPERTY(EditDefaultsOnly, Category = "MapNodeActorCreate")
        TSubclassOf<ASkeletonArcherCharacter> BP_ArcherCharacter;

    //UPROPERTY(EditDefaultsOnly, Category = "MapNodeActorCreate")
    //    TSubclassOf<ATree> BP_Tree;

    //UPROPERTY(EditDefaultsOnly, Category = "MapNodeActorCreate")
    //    TSubclassOf<ABarrier_1> BP_Barrier_1;

    //UPROPERTY(EditDefaultsOnly, Category = "MapNodeActorCreate")
    //    TSubclassOf<ABarrier_2> BP_Barrier_2;

    void GenerateMainCharacter(AHexActor & _hexActor, FVector & m_SpawnMainCharacterCoordinate);

    void GenerateBarriers(Hex *hex, FTransform & transform, StepAccessibility & access);

    void GenerateMap
    (
          ViewCoordinateGenerator * _pViewCoordinateGenerator
        , TransformCoordinate * _pTransformCoordinate
        , Grid * m_pGrid
       // , Coordinate & m_SpawnMainCharacterCoordinate
    );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

    TSet <AHexActor*> m_MapNodes;
    TSet <ATree*> m_MapTree;
    TSet <ABarrier_1*> m_MapBarrier_1;
    TSet <ABarrier_2*> m_MapBarrier_2;
    TSet <ASkeletonArcherCharacter*> m_SkeletonArcherCharacter;
};
