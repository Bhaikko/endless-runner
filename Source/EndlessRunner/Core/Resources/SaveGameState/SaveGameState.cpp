// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameState.h"


void USaveGameState::SetHighScore(int32 NewHighScore) 
{
    HighScore = NewHighScore;
}

USaveGameState::USaveGameState() 
{
    // HighScore = -1;
}
