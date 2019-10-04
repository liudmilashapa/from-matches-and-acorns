// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TransformCoordinate.hpp"
#include "Coordinate.hpp"
#include "CoreMinimal.h"
#include <vector>


#include "HexActor.generated.h"

class AGod;
class ASkeletonArcherCharacter;
class ASkeletonGruntCharacter;
enum StepAccessibility;

UENUM(BlueprintType)
enum class EIsInPath : uint8
{
    Empty,
    InPath, 
    EnemyNext
};

UCLASS()
class LUTEST_2_API AHexActor : public AActor
{
    GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHexActor();
 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UStaticMeshComponent* MeshBarrier;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        bool access;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        bool m_onClicked = false;

    //UENUM ( BlueprintType)
    //enum class StepAccessibility : uint8
    //{
    //    Empty,
    //    haveBarriers
    //}

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    //    USpringArmComponent* SpringArm;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    //    UCameraComponent* Camera;



    UFUNCTION(BlueprintCallable)
        EIsInPath IsInPath();

    UFUNCTION(BlueprintCallable)
        int IsInPathNumber();

    UFUNCTION(BlueprintCallable)
        void onClick();

    UFUNCTION(BlueprintNativeEvent, Category = "Code And Blueprint Events")
        void InPathChanged();

 /*   UFUNCTION(BlueprintCallable)
        FVector & GetLogicCoordinate();
*/
    
//    void setViewCoordinate(Coordinate & _coordinate);
 
public:
    
    bool IsOnClick();
    void SetOnClick(bool click);

    bool HasEnemy();

    int GetMaxRangeOfDefeat();

    void SetInPath(EIsInPath value);
    void SetInPathNumber(int value);

    void SetMainCharacter(ASkeletonArcherCharacter * _character);

    ASkeletonArcherCharacter * GetMainCharacter();

    void addGruntCharacter(ASkeletonGruntCharacter * _grunt);

    /*   void setLogicPass();*/
    
private:

    EIsInPath m_inPath = EIsInPath::Empty;

    int m_inPathNumber = -1;


    ASkeletonArcherCharacter * m_mainCharacter;
    std::vector< ASkeletonGruntCharacter * > m_GruntCharactersVector;
   // FVector m_viewCoordinate;

};
