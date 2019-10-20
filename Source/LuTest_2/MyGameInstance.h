// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"


class AFightMapGenerator;
class AMyMapGenerator;


/**
 * 
 */
UCLASS()
class LUTEST_2_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

        UPROPERTY(EditDefaultsOnly)
        TSubclassOf<AFightMapGenerator> BP_FightWorldManager;

        UPROPERTY(EditDefaultsOnly)
        TSubclassOf<AMyMapGenerator> BP_MyMapManager;

        void LevelGeneratorCreate();

private:

    TSet <AFightMapGenerator*> m_FightWorldManager;
    TSet <AMyMapGenerator*> m_HexMapManager;
};
