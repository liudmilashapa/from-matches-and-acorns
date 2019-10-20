// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FightWorldManager.generated.h"

UENUM(BlueprintType)
enum class FightAction : uint8
{
    DefaultShot
    , RandomShot
    , Evade
    , Run
};

class Fight;
class ASkeletonArcherCharacter;
class ASkeletonGruntCharacter;
enum class EArcherAnimationState : uint8;
enum class EGruntAnimationState : uint8;

UCLASS()
class LUTEST_2_API AFightWorldManager : public AActor
{
	GENERATED_BODY()
	
public:	

    static AFightWorldManager * GetInstance();

    void ChangeMainCharacterStateToIdle();
    void ChangeEnemyCharacterStateToIdle();

    void SetMainCharacterAnimationState(EArcherAnimationState state);
    void SetEnemyCharacterAnimationState(EGruntAnimationState state);

	// Sets default values for this actor's properties
	AFightWorldManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ASkeletonArcherCharacter * m_mainCharActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ASkeletonGruntCharacter * m_enemyCharActor;

    UFUNCTION(BlueprintCallable, Category = "Main Character Action Callback")
        void MakeMainCharacterAction(FightAction _userSelectedAction);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Logic Events")
        void MainCharHealthBarUpdate (float newBarState);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Logic Events")
        void EnemyHealthBarUpdate(float newBarState);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Logic Events")
        void MainCharHealthStateUpdate(int currentHP, int maxHP);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Logic Events")
        void EnemyHealthStateUpdate(int currentHP, int maxHP);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Logic Events")
        void MainCharThrowStart();

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Logic Events")
        void EnemyCharThrowStart();

    UFUNCTION(BlueprintCallable, Category = "Game Logic Events")
        void SetInitialUIState();

private:

    Fight * m_fight;

    static AFightWorldManager * ms_currentActiveInstance;

    FTimerHandle MainCharTimerHandle;
    FTimerHandle EnemyTimerHandle;
};
