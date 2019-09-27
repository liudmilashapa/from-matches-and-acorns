// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <set>

#include"HexActor.h"

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMapGenerator.generated.h"


class Hex;
class AHexActor;
class ViewCoordinateGenerator;
class PathSearch;
class Grid;

UCLASS()
class LUTEST_2_API AMyMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyMapGenerator();

    UPROPERTY(VisibleAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
        class UBoxComponent * SpawnPoint;

    UPROPERTY(EditDefaultsOnly, Category = "MapNodeActorSpawning")
        TSubclassOf<AHexActor> BP_Hex;

    void GenerateMap
    (
          ViewCoordinateGenerator * _pViewCoordinateGenerator
        , TransformCoordinate * _pTransformCoordinate
        , Grid * m_pGrid
    );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

    TSet <AHexActor*> m_MapNodes;

};
