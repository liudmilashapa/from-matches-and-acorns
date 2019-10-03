// Fill out your copyright notice in the Description page of Project Settings.

#include "God.h"

#include "MyMapGenerator.h"
#include "TransformCoordinate.hpp"
#include "ViewCoordinateGenerator.hpp"
#include "PathSearch.hpp"
#include "HexActor.h"
#include"Hex.hpp"
#include"Grid.hpp"
#include "GameState.hpp"

#include "FightMapGenerator.h"
#include "CameraFightUtility.h"

#include "EngineUtils.h"
#include "LogMacros.h"

AGod * AGod::p_instance = nullptr;

// Sets default values
AGod::AGod()
{ 
    p_instance = this;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("PointSpawnMap"));
    RootComponent = SpawnPoint; 
    m_pGrid = new Grid();
    m_pViewCoordinateGenerator = new ViewCoordinateGenerator();
    m_pTransformCoordinate = new TransformCoordinate();
    m_pGameState = new GameState();

    //SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    //Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    //SpringArm->SetupAttachment(SpawnPoint);
    //Camera->SetupAttachment(SpringArm);

    
}


// Called when the game starts or when spawned
void AGod::BeginPlay()
{
	Super::BeginPlay();
    if (BP_MyMapGenerator)
    {
        FActorSpawnParameters spawnParams;
        spawnParams.Template = Cast<AActor>(*BP_MyMapGenerator);
        m_pAMyMapGenerator = GetWorld()->SpawnActor<AMyMapGenerator>(BP_MyMapGenerator, GetTransform(), spawnParams);
        GenerateMap();
        GenerateMainCharacter();
    }
   
}

// Called every frame
void AGod::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //PathSearch * pathSearch = PathSearch::getInstance();
    //if (!pathSearch->IsEmpty())
    //{
    //    pathSearch->RecalculateHexGrid();
    //}
}



void AGod::FindPath(AHexActor * sourseActor, AHexActor * destinationActor)
{
//    m_pPathSearch = new PathSearch(*m_pGrid);
//    //    pathSearch->RecalculateHexGrid();
//    Hex * sourseHex = &m_pTransformCoordinate->getHexEngine(*sourseActor);
//    Hex * destinationHex = &m_pTransformCoordinate->getHexEngine(*destinationActor);
//    m_pPathSearch->SetAllPathes(sourseHex);
//    std::vector<Hex *> inputPath;
//    m_pPathSearch->ConstructorPath(sourseHex, destinationHex, inputPath);
//    for (auto hex : inputPath)
//    {
//        AHexActor * actorHex = &m_pTransformCoordinate->getAHexActor(*hex);
//        actorHex->m_inPath = true;
//    }
//
}

void AGod::GenerateMap()
{
    m_pAMyMapGenerator->GenerateMap(m_pViewCoordinateGenerator, m_pTransformCoordinate, m_pGrid);
}



PathSearch & AGod::GetPathSearch()
{
    return *m_pPathSearch;
}

ViewCoordinateGenerator & AGod::GetViewCoordinateGenerator()
{
    return *m_pViewCoordinateGenerator;
}

TransformCoordinate & AGod::GetTransformCoordinate()
{
    return *m_pTransformCoordinate;
}

AMyMapGenerator & AGod::GetAMyMapGenerator()
{
    return *m_pAMyMapGenerator;
}

 void AGod::EscapeActorHexFromPath()
 {
     m_pGrid->EscapeNodeFromPath(m_pPathSearch->GetPath());
     for (auto hex : m_pPathSearch->GetHexInPath())
     { 
         AHexActor * actor = &m_pTransformCoordinate->getAHexActor(*hex);
         actor->SetInPath(false);
         actor->SetInPathNumber(-1);
     }
 
 }

 void AGod::СhangeGameState(AHexActor * actor)
 {
     if (m_pGrid->findNode(*m_pTransformCoordinate->getHexEngine(*actor))->m_acces != StepAccessibility::Empty)
     {
         return;
     }

     m_pGameState->addHex(actor);

     if (m_pPathSearch && !m_pPathSearch->IsPathEmpty())
     {
         EscapeActorHexFromPath();
     }

     if (m_pGameState->GetCurentGameState() == GameStateField::selected2Hex)
     {
         m_pPathSearch = new PathSearch(*m_pGrid);
         std::vector< Node *> inputPathVector;
         std::pair <AHexActor *, AHexActor* > pair = m_pGameState->GetClickActor();
         Hex * _sourseHex = m_pTransformCoordinate->getHexEngine(*pair.first);
         Hex * _destinationHex = m_pTransformCoordinate->getHexEngine(*pair.second);
         m_pPathSearch->CreatePath( _sourseHex, _destinationHex);
         inputPathVector = m_pPathSearch->GetPath();
         if (inputPathVector.size() == 1)
         {
             m_pGameState->clearSelection();
             m_pGameState->addHex(actor);

             return;
         }
         for (auto node : inputPathVector)
         {
             AHexActor * actorHex = &m_pTransformCoordinate->getAHexActor(*node->m_hex);
             actorHex->SetInPath(true);
             actorHex->SetInPathNumber(node->m_path);
         }
     }
     if (m_pGameState->GetCurentGameState() == GameStateField::clearField)
     {

     }
}

void AGod::HexActorOnClick(AHexActor * actor)
{
    СhangeGameState( actor); 
   // UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/MyContent/Maps/FightMap"), TRAVEL_Absolute);
   // ChangeLevel();

}

void AGod::GenerateMainCharacter()
{
    while (true)
    {
        //Coordinate coordinate(FMath::RandRange(0, 9), FMath::RandRange(0, 9), 0);
        Coordinate coordinate(m_SpawnMainCharacterCoordinate);

        Node * node = m_pGrid->GetNodeForCoordinates(coordinate);

        if (node && node->m_acces == StepAccessibility::Empty)
        {
            m_pAMyMapGenerator->GenerateMainCharacter(m_pTransformCoordinate->getAHexActor(*node->m_hex), m_SpawnMainCharacterCoordinate);
            break;
        }
      
       
    }
}

void AGod::ChangeLevel()
{
 //   UGameplayStatics::Get
//    FString levelName = GetWorld()->GetMapName();

    if (BP_FightMapGenerator)
    {
        FActorSpawnParameters spawnParams;
        spawnParams.Template = Cast<AActor>(*BP_FightMapGenerator);
        m_pFightMapGenerator = GetWorld()->SpawnActor<AFightMapGenerator>(BP_FightMapGenerator, GetTransform(), spawnParams);
    }
}

//start copypaste
//
//bool AGod::IsTwoOnClicked()
//{
//    AHexActor * actorHexSourse=nullptr;
//    AHexActor * actorHexDestination=nullptr;
//    for (auto actor : m_MapNodes)
//    {
//        if (actor->IsOnClick())
//        {
//            if (!actorHexSourse)
//            {
//                actorHexSourse = actor;
//            }
//            actorHexDestination = actor;
//        }
//    }
//    return (actorHexSourse && actorHexDestination);
//}


//void AGod::GenerateMapNodeActor(Generator::FloatPoint & generatedPlace, uint32 index)
//{
//    FActorSpawnParameters spawnParams;
//    spawnParams.Template = Cast<AActor>(*GalaxyNodeActorBP);
//    FTransform transform = GetTransform();
//    transform.SetLocation(FVector((generatedPlace.x - 0.5)*PlanetDistanceScaleFactor, (generatedPlace.y - 0.5)*PlanetDistanceScaleFactor, 0));
//    AGalaxyMapNodeActor * actor = GetWorld()->SpawnActor<AGalaxyMapNodeActor>(GalaxyNodeActorBP, transform, spawnParams);
//    actor->NodeDifficulty = static_cast<ENodeDifficultyEnum>(rand() % 3);
//    actor->Index = index;
//    m_MapNodes.Add(actor);
//}
