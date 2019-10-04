
#include "GameState.hpp"

#include "HexActor.h"
#include "SkeletonArcherCharacter.h"
#include "ArcherAnimInstance.h"

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
       
        if (actor->GetMainCharacter())
        { 
            actor->SetOnClick(true);
            m_pSourseHexActor = actor;
            m_curentFieldState = GameStateField::selected1Hex;
        }
    }
    else if (actor != m_pSourseHexActor)
    {
        if (m_pDestinationHexActor && actor == m_pDestinationHexActor)
        {
            m_curentFieldState = GameStateField::selectedFinalHex;
        }
        else
        {
            m_pDestinationHexActor = actor;
            m_curentFieldState = GameStateField::selected2Hex;
            actor->SetOnClick(true);
        }
    }
    else 
    {
        clearSelection();
    }
}

void GameState::startMoveCharacter()
{
    ASkeletonArcherCharacter* pCharacter = m_pSourseHexActor->GetMainCharacter();

    UArcherAnimInstance* asArcherAnimInst = Cast<UArcherAnimInstance>(pCharacter->GetMesh()->GetAnimInstance());

    if (asArcherAnimInst)
    {
        asArcherAnimInst->ArcherAnimationState = EArcherAnimationState::Run;
        m_curentFieldState = GameStateField::characterMove;
    }
}

void GameState::endMoveCharacter()
{
    ASkeletonArcherCharacter* pCharacter = m_pSourseHexActor->GetMainCharacter();
    UArcherAnimInstance* asArcherAnimInst = Cast<UArcherAnimInstance>(pCharacter->GetMesh()->GetAnimInstance());
    if (asArcherAnimInst)
    {
        asArcherAnimInst->ArcherAnimationState = EArcherAnimationState::Idle;
    }

    m_pDestinationHexActor->SetMainCharacter(pCharacter);
    m_pSourseHexActor->SetMainCharacter(nullptr);

    clearSelection();
}

void GameState::changeState()
{

}


void GameState::clearSelection()
{
    if (m_pSourseHexActor)
    {
        m_pSourseHexActor->SetOnClick(false);
    }
    if (m_pDestinationHexActor)
    {
        m_pDestinationHexActor->SetOnClick(false);
    }
    m_pDestinationHexActor = m_pSourseHexActor = nullptr;
    m_curentFieldState = GameStateField::clearField;
}

