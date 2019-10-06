#pragma once

enum class FightState
{
      MainCharacterWaitForAction
    , MainCharacterPerformAction
    , EnemyCharacterPerformAction
    , MainCharacterDefeated
    , EnemyCharacterDefeated
};

class ASkeletonArcherCharacter;
class ASkeletonGruntCharacter;

enum class FightAction : uint8;

class Fight
{
public:

    Fight(ASkeletonArcherCharacter * _mainCharacter, ASkeletonGruntCharacter * _enemyCharacter);

    void MakeMainCharacterAction(FightAction _action);

private:

    void MakeAction(FightAction _action);
    void ProcessAndChangeCurrentState();
    void MakeEnemyAction();

    ASkeletonArcherCharacter * m_mainCharActor;
    ASkeletonGruntCharacter * m_enemyCharActor;

    FightState m_fightState;
};