
#include "GameState.hpp"

#include "HexActor.h"


GameStateField GameState::GetCurentGameState()
{
    return m_curentFieldState;
}

std::pair <AHexActor *, AHexActor* > GameState::GetClickActor()
{
    return std::make_pair( m_pSourseHexActor, m_pDestinationHexActor);
}

void GameState::addHex(AHexActor * actor)
{
    if (!m_pSourseHexActor)
    {
        m_pSourseHexActor = actor;
        m_curentFieldState = GameStateField::selected1Hex;
    }
    else if (!m_pDestinationHexActor || actor != m_pSourseHexActor)
    {
        m_pDestinationHexActor = actor;
        m_curentFieldState = GameStateField::selected2Hex;
    }
    else 
    {
        m_pDestinationHexActor = nullptr;
        m_pSourseHexActor = nullptr;
        m_curentFieldState = GameStateField::clearField;
    }
}