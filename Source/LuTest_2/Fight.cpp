#include "Fight.h"
#include "FightWorldManager.h"
#include "CharacterInfo.h"

#include "SkeletonArcherCharacter.h"
#include "SkeletonGruntCharacter.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include <utility>

Fight::Fight(ASkeletonArcherCharacter * _mainCharacter, ASkeletonGruntCharacter * _enemyCharacter)
{
    m_mainCharActor = _mainCharacter;
    m_enemyCharActor = _enemyCharacter;

    m_fightState = FightState::MainCharacterWaitForAction;
}

void Fight::MakeMainCharacterAction(FightAction _action)
{
    if (m_fightState == FightState::MainCharacterWaitForAction)
    {
        m_fightState = FightState::MainCharacterPerformAction;
        MakeAction(_action);
        ProcessAndChangeCurrentState();
    }
}

void Fight::MakeEnemyAction()
{
    if (m_fightState == FightState::EnemyCharacterPerformAction)
    {
        FightAction action = FightAction::DefaultShot;

        int actionRandomValue = FMath::RandRange(0, 100);

        bool isLowOnHP = m_enemyCharActor->GetCharacterInfo()->GetCurentHP() / m_enemyCharActor->GetCharacterInfo()->GetMaxHP() < 0.1;

        if (isLowOnHP && actionRandomValue > 80)
        {
            action = FightAction::Run;
        }
        else if (actionRandomValue > 0 && actionRandomValue < 75)
        {
            action = FightAction::DefaultShot;
        }
        else
        {
            action = FightAction::RandomShot;
        }

        MakeAction(action);
        ProcessAndChangeCurrentState();
    }
}

void Fight::MakeAction(FightAction _action)
{
    if (!(m_fightState == FightState::MainCharacterPerformAction || m_fightState == FightState::EnemyCharacterPerformAction))
    {
        return;
    }

    CharacterInfo * attackerInfo = m_mainCharActor->GetCharacterInfo();
    CharacterInfo * defenderInfo = m_enemyCharActor->GetCharacterInfo();

    if (m_fightState == FightState::EnemyCharacterPerformAction)
    {
        std::swap(attackerInfo, defenderInfo);
    }

    int attackValue = 0;

    switch (_action)
    {
        case FightAction::DefaultShot:
        {
            attackValue = attackerInfo->GetMainAttackRate();
            defenderInfo->SetCurentHP(defenderInfo->GetCurentHP() - attackValue);

            break;
        }
        case FightAction::RandomShot:
        {
            attackValue = attackerInfo->GetRandomAttackRate();
            defenderInfo->SetCurentHP(defenderInfo->GetCurentHP() - attackValue);

            break;
        }
        case FightAction::Evade:
        {
            // ??? Later

            break;
        }
        case FightAction::Run:
        {
            int runAttemptChance = FMath::RandRange(0, 100);

            if (runAttemptChance > 60)
            {
                UGameplayStatics::OpenLevel(m_mainCharActor->GetWorld(), TEXT("/Game/MyContent/Maps/HexMap"), TRAVEL_Absolute);

            }
            break;
        }

        default:
        break;
    }

    if (attackValue != 0)
    {
        float newHealthBarValue = static_cast<float>(defenderInfo->GetCurentHP()) / defenderInfo->GetMaxHP();
        AFightWorldManager* worldManager = AFightWorldManager::GetInstance();

        if (m_fightState == FightState::MainCharacterPerformAction)
        {
            worldManager->EnemyHealthBarUpdate(newHealthBarValue);
            worldManager->EnemyHealthStateUpdate( defenderInfo->GetCurentHP(), defenderInfo->GetMaxHP() );
        }
        else
        {
            worldManager->MainCharHealthBarUpdate(newHealthBarValue);
            worldManager->MainCharHealthStateUpdate(defenderInfo->GetCurentHP(), defenderInfo->GetMaxHP());
        }
    }
}

void Fight::ProcessAndChangeCurrentState()
{
    bool isMainCharAlive = m_mainCharActor->GetCharacterInfo()->isAlive();
    bool isEnemyCharAlive = m_enemyCharActor->GetCharacterInfo()->isAlive();

    if (!isMainCharAlive)
    {
        m_fightState = FightState::MainCharacterDefeated;
        // move to next state
        return;
    }
    if (!isEnemyCharAlive)
    {
        m_fightState = FightState::EnemyCharacterDefeated;

        UGameplayStatics::OpenLevel(m_mainCharActor->GetWorld(), TEXT("/Game/MyContent/Maps/HexMap"), TRAVEL_Absolute);

        return;
    }

    switch (m_fightState)
    {
        case FightState::MainCharacterPerformAction:
        {
            m_fightState = FightState::EnemyCharacterPerformAction;
            MakeEnemyAction();
            break;
        }
        case FightState::EnemyCharacterPerformAction:
        {
            m_fightState = FightState::MainCharacterWaitForAction;
            break;
        }
        default:
            break;
    }
}