// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
    

    ShowMouseCursor = true;
    ShowHideCursor();
}

void AMyPlayerController::ShowHideCursor()
{
    if (ShowMouseCursor == true)
    {
        bShowMouseCursor = true; 
        bEnableClickEvents = true;
        bEnableMouseOverEvents = true;
        DefaultMouseCursor = EMouseCursor::Hand;
    }
    else 
    {
        bShowMouseCursor = false;
        bEnableClickEvents = false;
        bEnableMouseOverEvents = false;
    }


}