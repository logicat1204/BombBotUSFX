// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBOT_API AGameModeMainMenu : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	AGameModeMainMenu();

	virtual void BeginPlay() override;

	USoundBase* LevelMusicM;
};
