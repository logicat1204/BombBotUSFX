// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ILevels_Builder.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UILevels_Builder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOMBBOT_API IILevels_Builder
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BuildMap() = 0;
	virtual void BuildEnemy(int32 CantidadEnemigos) = 0;
	virtual void BuildPowerUps(int32 CantidadPowerUps) = 0;
	virtual void BuildPortals() = 0;
	virtual void SetStartPosition() = 0;
	virtual void FinalizeLevel() = 0;
};
