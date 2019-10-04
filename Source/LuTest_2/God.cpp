// Fill out your copyright notice in the Description page of Project Settings.

#include "God.h"

#include "MyMapGenerator.h"
#include "TransformCoordinate.hpp"
#include "ViewCoordinateGenerator.hpp"
#include "PathSearch.hpp"
#include "HexActor.h"
#include "Hex.hpp"
#include "Grid.hpp"
#include "GameState.hpp"

#include "SkeletonArcherCharacter.h"
#include "ArcherAnimInstance.h"
#include "FightMapGenerator.h"
#include "CameraFightUtility.h"

#include "Kismet/KismetMathLibrary.h"

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
        GenerateEnemiesCharacter();
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

    if (m_pGameState && m_pGameState->GetCurentGameState() == GameStateField::characterMove)
    {
 
        if (m_currentPath.size() == 0)
        {
            m_pGameState->endMoveCharacter();
            return;
        }

        ASkeletonArcherCharacter * mainChar = m_pGameState->GetClickActor().first->GetMainCharacter();
        FVector mainCharacterLocation = mainChar->GetActorLocation();

        FVector destinationLocation = m_pTransformCoordinate->getAHexActor(*m_currentPath.back()->m_hex).GetActorLocation();
        destinationLocation.Z = mainCharacterLocation.Z;

        if (mainCharacterLocation.Equals(destinationLocation))
        {
            m_currentPath.pop_back();
        }
        else 
        {
            FVector newPosition = FMath::VInterpTo(mainCharacterLocation, destinationLocation,  DeltaTime, 5 );
            
            FVector rotationVector =  newPosition - mainChar->GetActorLocation();
            FRotator  rotator = UKismetMathLibrary::MakeRotFromX(rotationVector);
            //mainChar->SetActorRotation(FVector(0.0,0.0, rotator.Yaw)),
            mainChar->SetActorLocationAndRotation(newPosition, rotator);
        }
    }
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
         actor->SetInPath(EIsInPath::Empty);
         actor->SetInPathNumber(-1);
         actor->SetOnClick(false);
     }
 
 }

 void AGod::СhangeGameState(AHexActor * actor)
 {
     if (m_pGameState->GetCurentGameState() == GameStateField::characterMove)
     {
         return;
     }

     if (m_pGrid->findNode(*m_pTransformCoordinate->getHexEngine(*actor))->m_acces != StepAccessibility::Empty)
     {
         return;
     }

    if (m_pPathSearch && !m_pPathSearch->IsPathEmpty())
    {
         EscapeActorHexFromPath();
    }

     m_pGameState->addHex(actor);

    
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
      /*   for (auto node : inputPathVector)
         {
             AHexActor * actorHex = &m_pTransformCoordinate->getAHexActor(*node->m_hex);
             if (m_pPathSearch->IsEnemyNext(actorHex))
             {
                 actorHex->SetInPath(EIsInPath::EnemyNext);
             }
             else
             {
                 actorHex->SetInPath(EIsInPath::InPath);
                 actorHex->SetInPathNumber(node->m_path);
             }
         }*/
     }
     if (m_pGameState->GetCurentGameState() == GameStateField::selectedFinalHex)
     {
         m_currentPath = m_pPathSearch->GetPath();
         m_pGameState->startMoveCharacter();
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
        Coordinate coordinate(FMath::RandRange(8, 12), FMath::RandRange(8, 12), 0);

        Node * node = m_pGrid->GetNodeForCoordinates(coordinate);

        if (node && node->m_acces == StepAccessibility::Empty)
        {
            m_pAMyMapGenerator->GenerateMainCharacter(m_pTransformCoordinate->getAHexActor(*node->m_hex));
            break;
        }
      
       
    }
}

void AGod::GenerateEnemiesCharacter()
{
    int enemyCount=0;
    while (enemyCount < 20)
    {

        Coordinate coordinate(FMath::RandRange(0, 29), FMath::RandRange(0, 29), 0);

        Node * node = m_pGrid->GetNodeForCoordinates(coordinate);
        if (m_pTransformCoordinate->getAHexActor(*node->m_hex).GetMainCharacter() && !m_pTransformCoordinate->getAHexActor(*node->m_hex).HasEnemy())
        {
            continue;
        }
        if (node && node->m_acces == StepAccessibility::Empty)
        {
            m_pAMyMapGenerator->GenerateEnemyCharacter(m_pTransformCoordinate->getAHexActor(*node->m_hex));
            enemyCount++;
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
