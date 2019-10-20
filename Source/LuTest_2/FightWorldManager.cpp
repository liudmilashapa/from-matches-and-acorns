// Fill out your copyright notice in the Description page of Project Settings.


#include "FightWorldManager.h"
#include "Fight.h"

#include "SkeletonArcherCharacter.h"
#include "SkeletonGruntCharacter.h"
#include "GruntAnimInstance.h"
#include "ArcherAnimInstance.h"

#include "CharacterInfo.h"

#include <thread>

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

void AFightWorldManager::ChangeMainCharacterStateToIdle()
{
    UArcherAnimInstance* asArcherAnimInst = Cast<UArcherAnimInstance>(m_mainCharActor->GetMesh()->GetAnimInstance());
    asArcherAnimInst->ArcherAnimationState = EArcherAnimationState::Idle;

}

void AFightWorldManager::ChangeEnemyCharacterStateToIdle()
{
    UGruntAnimInstance* asGruntAnimInst = Cast<UGruntAnimInstance>(m_enemyCharActor->GetMesh()->GetAnimInstance());
    asGruntAnimInst->GruntAnimationState = EGruntAnimationState::Idle;
}

void AFightWorldManager::SetMainCharacterAnimationState(EArcherAnimationState state)
{
    UArcherAnimInstance* asArcherAnimInst = Cast<UArcherAnimInstance>(m_mainCharActor->GetMesh()->GetAnimInstance());
    asArcherAnimInst->ArcherAnimationState = state;

    GetWorld()->GetTimerManager().SetTimer(MainCharTimerHandle, this, &AFightWorldManager::ChangeMainCharacterStateToIdle, 3.0f, false);
   // std::this_thread::sleep_for(std::chrono::milliseconds(420));
}


void AFightWorldManager::SetEnemyCharacterAnimationState(EGruntAnimationState state)
{
    UGruntAnimInstance* asGruntAnimInst = Cast<UGruntAnimInstance>(m_enemyCharActor->GetMesh()->GetAnimInstance());
    asGruntAnimInst->GruntAnimationState = state;
    GetWorld()->GetTimerManager().SetTimer(EnemyTimerHandle, this, &AFightWorldManager::ChangeEnemyCharacterStateToIdle, 3.0f, false);
    //std::this_thread::sleep_for(std::chrono::milliseconds(420));
}

AFightWorldManager* AFightWorldManager::ms_currentActiveInstance(nullptr);