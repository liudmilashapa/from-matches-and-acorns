#include "TransformCoordinate.hpp"

#include "Hex.hpp"
#include "HexActor.h"

#include <AssertionMacros.h>


void TransformCoordinate::addElement(AHexActor * actor, Hex * hex)
{
    if (ActorHexToEngineHex.find(actor) == ActorHexToEngineHex.end())
    {
        ActorHexToEngineHex.insert({ actor, hex });
    }
    if (EngineHexToActorHex.find(hex) == EngineHexToActorHex.end())
    {
        EngineHexToActorHex.insert({ hex, actor });
    }
}

AHexActor & TransformCoordinate::getAHexActor(Hex  & hex)
{
    auto it = EngineHexToActorHex.find(&hex);
    check(it != EngineHexToActorHex.end());
    return *it->second;
}

Hex & TransformCoordinate::getHexEngine(AHexActor & actor)
{
    auto it = ActorHexToEngineHex.find(&actor);
    check(it != ActorHexToEngineHex.end());
    return *it->second;
    
   
}

//bool TransformCoordinate::IsLogicCoordinateValid(Coordinate & _coordinate)
//{
//    
//    return (std::find_if(EngineHexToActorHex.begin(), EngineHexToActorHex.end(), [_coordinate](Hex* hex)
//        {
//            return hex->GetLogicCoordinates().IsEqual( _coordinate);
//        })!= EngineHexToActorHex.end());
//}