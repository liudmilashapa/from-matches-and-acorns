// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMapGenerator.h"

#include"Tree.h"
#include "SkeletonArcherCharacter.h"
#include "SkeletonGruntCharacter.h"
#include "Hex.hpp"
#include "Grid.hpp"
#include "TransformCoordinate.hpp"
#include "ViewCoordinateGenerator.hpp"
#include "PathSearch.hpp"
#include "HexActor.h"

#include "Math/UnrealMathUtility.h"

// Sets default values
AMyMapGenerator::AMyMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("PointSpawnMap"));

}

// Called when the game starts or when spawned
void AMyMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyMapGenerator::GenerateMainCharacter(AHexActor & _hexActor)
{
    if (BP_ArcherCharacter)
    {
        FActorSpawnParameters spawnParams;

        FTransform transform = GetTransform();
        FVector hexLocation = _hexActor.GetActorTransform().GetLocation();
        //hexLocation.X -= ViewCoordinateGenerator::innerRadius / 2;
        //hexLocation.Y -= ViewCoordinateGenerator::innerRadius / 2;

        hexLocation.Z += 20;
        transform.SetLocation(hexLocation);
        transform.SetScale3D(FVector(0.2, 0.2, 0.2));
        ASkeletonArcherCharacter * actor = GetWorld()->SpawnActor<ASkeletonArcherCharacter>(BP_ArcherCharacter, transform, spawnParams);
        m_SkeletonArcherCharacter.Add(actor);
        _hexActor.SetMainCharacter(actor);
    }
}

void AMyMapGenerator::GenerateEnemyCharacter(AHexActor & _hexActor)
{
    if (BP_GruntCharacter)
    {
       
        FActorSpawnParameters spawnParams;

        FTransform transform = GetTransform();
        FVector hexLocation = _hexActor.GetActorTransform().GetLocation();
        //hexLocation.X -= ViewCoordinateGenerator::innerRadius / 2;
        //hexLocation.Y -= ViewCoordinateGenerator::innerRadius / 2;

        hexLocation.Z += 15;
        transform.SetLocation(hexLocation);
        transform.SetScale3D(FVector(0.15, 0.15, 0.15));
        ASkeletonGruntCharacter * actor = GetWorld()->SpawnActor<ASkeletonGruntCharacter>(BP_GruntCharacter, transform, spawnParams);
        m_SkeletonGruntCharacter.Add(actor);
        _hexActor.addGruntCharacter(actor);
    }
}

//void AMyMapGenerator::GenerateEnemy(Hex *hex, FTransform & transform, StepAccessibility & access)


void AMyMapGenerator::GenerateMap
(
      ViewCoordinateGenerator * _pViewCoordinateGenerator
    , TransformCoordinate * _pTransformCoordinate
    , Grid * m_pGrid
    //, Coordinate & m_SpawnMainCharacterCoordinate
)
{
    if (BP_Hex)
    {
        FVector StartPoint = SpawnPoint->Bounds.Origin;
        for (int i = 0; i < 30; ++i)
        {
            for (int j = 0; j < 30; ++j)
            {  
               
                Hex * hex = new Hex(i, j);
                FActorSpawnParameters spawnParams;
                spawnParams.Template = Cast<AActor>(*BP_Hex);
                
                FTransform transform = GetTransform();
                
                Coordinate * hex2dCoordinates = hex->Get2DCoordinates();
                FVector locationVector(_pViewCoordinateGenerator->generateViewCoordinate(*hex2dCoordinates, StartPoint));
                transform.SetLocation(locationVector);
                
                AHexActor * actor = GetWorld()->SpawnActor<AHexActor>(BP_Hex, transform, spawnParams);
               
                m_MapNodes.Add(actor);
                _pTransformCoordinate->addElement(actor, hex);

         
                //GenerateBarriers(hex, transform, access);
                m_pGrid->addNode(hex, actor->access); 
             
            }
        }
        
     //   pathSearch->RecalculateHexGrid();
      // FindPath(sourseActor, destinationActor);



        //  m_MapDataGenerator.GenerateSequence(pointsCount, Generator::ZoneKind::Rectangular, seed);

        //uint32 index = 0;
        //for (Generator::FloatPoint & point : m_MapDataGenerator)
        //{
        //    GenerateMapNodeActor(point, index);
        //    index++;
        //}
    }
}
