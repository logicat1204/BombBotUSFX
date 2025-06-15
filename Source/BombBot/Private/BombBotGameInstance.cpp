// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBotGameInstance.h"

void UBombBotGameInstance::AddScore(int32 Amount)
{
	PlayerScore += Amount;
}

void UBombBotGameInstance::ResetScore()
{
	PlayerScore = 0;
}
