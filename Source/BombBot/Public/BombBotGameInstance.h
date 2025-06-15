// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BombBotGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBOT_API UBombBotGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    // Puntuación actual del jugador
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Score")
    int32 PlayerScore=0;

public:
    // Funciones para modificar la puntuación
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Score")
    void ResetScore();

	int32 GetScore()
	{
		return PlayerScore;
	}
};
