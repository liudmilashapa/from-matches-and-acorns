// Fill out your copyright notice in the Description page of Project Settings.


#include "FightWorldManager.h"
#include "Fight.h"

#include "SkeletonArcherCharacter.h"
#include "SkeletonGruntCharacter.h"
#include "CharacterInfo.h"

#include "God.h"
#include "MyMapGenerator.h"

// Sets default values
AFightWorldManager::AFightWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    ms_currentActiveInstance = this;
    m_fight = nullptr;
}

// Called when the game starts or when spawned
void AFightWorldManager::BeginPlay()
{
	Super::BeginPlay();
	
    if (!m_fight)
    {
        m_fight = new Fight(m_mainCharActor, m_enemyCharActor);

        CharacterInfo * mainCharInfo = m_mainCharActor->GetCharacterInfo();
        CharacterInfo * enemyCharInfo = m_enemyCharActor->GetCharacterInfo();

        mainCharInfo->SetCurentHP(mainCharInfo->GetMaxHP());
        enemyCharInfo->SetCurentHP(enemyCharInfo->GetMaxHP());
    }
}

// Called every frame
void AFightWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFightWorldManager::MakeMainCharacterAction(FightAction _userSelectedAction)
{
    m_fight->MakeMainCharacterAction(_userSelectedAction);
}

void AFightWorldManager::SetInitialUIState()
{
    MainCharHealthBarUpdate(1.0f);
    int mainCharMaxHP = m_mainCharActor->GetCharacterInfo()->GetMaxHP();
    MainCharHealthStateUpdate(mainCharMaxHP, mainCharMaxHP);

    EnemyHealthBarUpdate(1.0f);
    int enemyCharMaxHP = m_enemyCharActor->GetCharacterInfo()->GetMaxHP();
    EnemyHealthStateUpdate(enemyCharMaxHP, enemyCharMaxHP);
}

AFightWorldManager * AFightWorldManager::GetInstance()
{
    return ms_currentActiveInstance;
}

AFightWorldManager* AFightWorldManager::ms_currentActiveInstance(nullptr);