#pragma once

#include "Coordinate.hpp"
#include <map>
#include <algorithm>
//#include <FVector>




class AHexActor;
class Hex;

class TransformCoordinate
{
private:

    std::map<AHexActor *, Hex *> ActorHexToEngineHex;
    std::map<Hex *, AHexActor *>EngineHexToActorHex;

public:
   
    void addElement(AHexActor * actor, Hex * hex);

    AHexActor &  getAHexActor(Hex  & hex);
    
    Hex * getHexEngine(AHexActor & actor);

    void Clear() { ActorHexToEngineHex.clear(); EngineHexToActorHex.clear(); }

    
//    bool IsLogicCoordinateValid(Coordinate &_coordinate);
};