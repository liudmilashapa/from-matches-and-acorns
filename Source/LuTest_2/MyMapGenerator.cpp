// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMapGenerator.h"

#include "Hex.hpp"
#include "Grid.hpp"
#include "TransformCoordinate.hpp"
#include "ViewCoordinateGenerator.hpp"
#include "PathSearch.hpp"
#include "HexActor.h"


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


void AMyMapGenerator::GenerateMap(
      ViewCoordinateGenerator * _pViewCoordinateGenerator
    , TransformCoordinate * _pTransformCoordinate
    , Grid * m_pGrid)
{
    if (BP_Hex)
    {
        FVector StartPoint = SpawnPoint->Bounds.Origin;
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                                Hex * hex = new Hex(i, j);
                
                                m_pGrid->addNode(hex);
                                FActorSpawnParameters spawnParams;
                                spawnParams.Template = Cast<AActor>(*BP_Hex);
                
                                FTransform transform = GetTransform();
                
                                Coordinate hex2dCoordinates = hex->Get2DCoordinates();
                                FVector locationVector(_pViewCoordinateGenerator->generateViewCoordinate(hex2dCoordinates, StartPoint));
                                transform.SetLocation(locationVector);
                
                                AHexActor * actor = GetWorld()->SpawnActor<AHexActor>(BP_Hex, transform, spawnParams);
                                m_MapNodes.Add(actor);
                //                actor->setViewCoordinate(m_MapDataGenerator.generateViewCoordinate(hex2dCoordinates));
                                _pTransformCoordinate->addElement(actor, hex);
                               /* if (i == 0 && j == 0)
                                {
                                     sourseActor = actor;
                                }

                                if (i == 4 && j == 4)
                                {
                                    destinationActor = actor;
                                }*/
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
