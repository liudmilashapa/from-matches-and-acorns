// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#include <vector>

#include "God.generated.h"

class AFightMapGenerator;
class ACameraFightUtility;
class PathSearch;
class ViewCoordinateGenerator;
class TransformCoordinate;
class AMyMapGenerator;
class GameState;
class Hex;
class AHexActor;
class ViewCoordinateGenerator;
class PathSearch;
class Grid;
struct Node;
//enum class EArcherAnimationState : uint8;


UCLASS()
class LUTEST_2_API AGod : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AGod();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;


    UPROPERTY(VisibleAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
        class UBoxComponent * SpawnPoint;

    UPROPERTY(EditDefaultsOnly, Category = "WorldGeneration")
        TSubclassOf<AMyMapGenerator> BP_MyMapGenerator;

    UPROPERTY(EditDefaultsOnly, Category = "WorldGeneration")
        TSubclassOf<AFightMapGenerator> BP_FightMapGenerator;

    UPROPERTY(BlueprintReadWrite, Category = "WorldGeneration")
        AMyMapGenerator* MapGenerator;

 //   UPROPERTY(BlueprintReadOnly, Category = "WorldGeneration")
 //      FVector  m_SpawnMainCharacterCoordinate = FVector(10, 10, 0);

    UPROPERTY(BlueprintReadOnly, Category = "WorldGeneration")
        bool m_IsLevelGenerated;

    UFUNCTION(BlueprintCallable, Category = "WorldGeneration")
        void GenerateMap();


    //UPROPERTY(BlueprintReadWrite, Category = "NodesVisualConfiguration")
    //    float PlanetDistanceScaleFactor;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    //    USpringArmComponent* SpringArm;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    //    UCameraComponent* Camera;

protected:

 //   void GenerateMapNodeActor(Generator::FloatPoint & generatedPlace, uint32 index);

public:

    PathSearch & GetPathSearch();
    
    ViewCoordinateGenerator & GetViewCoordinateGenerator();
    
    TransformCoordinate & GetTransformCoordinate();

    AMyMapGenerator & GetAMyMapGenerator();
    
    static AGod * GetGodClass()
    {
     return p_instance;
    }

    void MoveMainCharacter();

    void EscapeActorHexFromPath();

    void  СhangeGameState(AHexActor * actor);

    void HexActorOnClick(AHexActor * actor);

    void GenerateMainCharacter();

    void GenerateEnemiesCharacter();


    void ChangeLevel();

private:
    
    static  AGod * p_instance;

    AMyMapGenerator * m_pAMyMapGenerator;
    PathSearch * m_pPathSearch;
    ViewCoordinateGenerator * m_pViewCoordinateGenerator;
    TransformCoordinate * m_pTransformCoordinate;
    Grid * m_pGrid;
    GameState * m_pGameState;
    
    AFightMapGenerator * m_pFightMapGenerator;
    ACameraFightUtility * m_cameraFightUtility;

    std::vector<Node *> m_currentPath;

    Node* m_currentActiveNode = nullptr;
    float m_currentLerpAlphaForMovement = 0;
};

