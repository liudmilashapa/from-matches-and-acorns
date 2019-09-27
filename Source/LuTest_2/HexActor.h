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

#include "HexActor.generated.h"

class AGod;

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
        USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UCameraComponent* Camera;


    UFUNCTION(BlueprintCallable)
        bool IsInPath();

    UFUNCTION(BlueprintCallable)
        int IsInPathNumber();


    UFUNCTION(BlueprintCallable)
        void onClick();

    /*UFUNCTION(BlueprintCallable)
        FVector GetLogicCoordinate();
*/
    
//    void setViewCoordinate(Coordinate & _coordinate);
 
public:
    
    bool IsOnClick();

    void SetInPath(bool value);
    void SetInPathNumber(int value);
    /*   void setLogicPass();*/
    
private:

    bool m_inPath = false;
    int m_inPathNumber = -1;

    bool m_onClicked = false;

   // FVector m_viewCoordinate;

};
