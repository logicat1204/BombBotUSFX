// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombBotGameMode.generated.h"

UCLASS(minimalapi)
class ABombBotGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABombBotGameMode();

	virtual void BeginPlay() override;

	USoundBase* LevelMusic;
};



