#pragma once

#include <utility>

class AHexActor;




enum class GameStateField
{
    clearField,
    selected1Hex,
    selected2Hex,
    change1Hex,
    change2Hex,
    selectedFinalHex,
    characterMove,

};



class GameState
{

public:

    GameStateField GetCurentGameState();
    std::pair <AHexActor *, AHexActor* > GetClickActor();
    void addHex(AHexActor * actor);
    void clearSelection();

private:

    GameStateField m_curentFieldState = GameStateField::clearField;
    AHexActor * m_pSourseHexActor = nullptr;
    AHexActor * m_pDestinationHexActor = nullptr;

};
