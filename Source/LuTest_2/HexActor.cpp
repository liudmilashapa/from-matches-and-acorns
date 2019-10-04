 // Fill out your copyright notice in the Description page of Project Settings.

#include "HexActor.h"

#include "Grid.hpp"
#include "PathSearch.hpp"
#include "Hex.hpp"
#include "God.h"

// Sets default values
AHexActor::AHexActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    MeshBarrier = CreateDefaultSubobject<UStaticMeshComponent>("MeshBarrier");
    RootComponent = Mesh;
    Mesh->SetMobility(EComponentMobility::Static);
//    MeshBarrier->SetMobility(EComponentMobility::Stationary);
}

// Called when the game starts or when spawned
void AHexActor::BeginPlay()
{
	Super::BeginPlay();
  
}

// Called every frame
void AHexActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AHexActor::setViewCoordinate(Coordinate & _coordinate)
//{
//    m_viewCoordinate = _coordinate;
//}
//


 EIsInPath AHexActor::IsInPath()
{
    return m_inPath;
}

int AHexActor::IsInPathNumber()
{
    return m_inPathNumber;
}


void AHexActor::onClick()
{
    AGod * God = AGod::GetGodClass();
    God->HexActorOnClick(this);

/*

    PathSearch * pathSearch = PathSearch::getInstance();
    TransformCoordinate * transformCoordinate = TransformCoordinate::getInstance();
    std::vector<Node *> Neighbors = pathSearch->GetNeighbors(&transformCoordinate->getHexEngine(*this));
    for (auto node : Neighbors)
    {
        AHexActor * actorHex = &transformCoordinate->getAHexActor(*node->m_hex);
        actorHex->m_inPath = true;
    }*/
}


//FVector & AHexActor::GetLogicCoordinate()
//{
//    AGod * God = AGod::GetGodClass();
//    Hex * hex = God->GetTransformCoordinate().getHexEngine(*this);
//    if (hex)
//    {
//        return hex->Get2DCoordinates()->GetFVector();
//    }
//    else
//    {
//        FVector vector = FVector(-1000,-1000,-1000);
//        return vector;
//    }
//
//}
//



bool AHexActor::IsOnClick()
{
    return m_onClicked;
}


void AHexActor::SetOnClick(bool click)
{
    m_onClicked = click;
    InPathChanged();
}

bool AHexActor::HasEnemy()
{
    return m_GruntCharactersVector.size() != 0;
}

//int AHexActor::GetMaxRangeOfDefeat()
//{
//    if (!m_GruntCharactersVector.empty())
//    {
//        return  m_GruntCharactersVector.at(0)->GetRangeOfDefeat();
//    }
//}

void AHexActor::SetInPath(EIsInPath value)
{
    m_inPath = value;
    InPathChanged();
}

void AHexActor::SetInPathNumber(int value)
{
    m_inPathNumber = value;


}

void AHexActor::SetMainCharacter(ASkeletonArcherCharacter * _character)
{
    m_mainCharacter = _character;
}

ASkeletonArcherCharacter * AHexActor::GetMainCharacter( )
{
    return m_mainCharacter;
}

void AHexActor::addGruntCharacter(ASkeletonGruntCharacter * _grunt)
{
    if (std::find(m_GruntCharactersVector.begin(), m_GruntCharactersVector.end(), _grunt) == m_GruntCharactersVector.end())
    {
        m_GruntCharactersVector.push_back(_grunt);
    }
}

void AHexActor::InPathChanged_Implementation()
{
}

//void AHexActor::onClick()
//{
//    PathSearch * pathSearch = PathSearch::getInstance();
//    TransformCoordinate * transformCoordinate = TransformCoordinate::getInstance();
//    std::vector<Node *> Neighbors = pathSearch->GetNeighbors(&transformCoordinate->getHexEngine(*this));
//    for (auto node : Neighbors)
//    {
//        AHexActor * actorHex = &transformCoordinate->getAHexActor(*node->m_hex);
//        actorHex->m_inPath = true;
//    }
//}




/*void setLogicPass()
{
    TransformCoordinate * transformCoordinate = TransformCoordinate::getInstance();
    return transformCoordinate->getHexEngine(*this).;
}
*/

