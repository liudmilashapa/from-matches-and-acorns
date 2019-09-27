 // Fill out your copyright notice in the Description page of Project Settings.

#include "HexActor.h"

#include "PathSearch.hpp"
#include "Hex.hpp"
#include "God.h"

// Sets default values
AHexActor::AHexActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    RootComponent = Mesh;
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
//FVector AHexActor::GetLogicCoordinate()
//{
//    TransformCoordinate * transformCoordinate = TransformCoordinate::getInstance();
//    return transformCoordinate->getHexEngine(*this).GetLogicCoordinates().ToFVector();
//
//}


bool AHexActor::IsInPath()
{
    return m_inPath;
}

int AHexActor::IsInPathNumber()
{
    return m_inPathNumber;
}


void AHexActor::onClick()
{
    m_onClicked = true;
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

bool AHexActor::IsOnClick()
{
    return m_onClicked;
}

void AHexActor::SetInPath(bool value)
{
    m_inPath = value;
}

void AHexActor::SetInPathNumber(int value)
{
    m_inPathNumber = value;


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

