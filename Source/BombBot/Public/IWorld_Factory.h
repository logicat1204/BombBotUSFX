// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World1_FactoryBloques.h"
#include "UObject/Interface.h"
#include "IWorld_Factory.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIWorld_Factory : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOMBBOT_API IIWorld_Factory
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//CREACION DE FABRICAS
	AWorld1_FactoryBloques* FabricaBloques;

	virtual void CreateMap() = 0;
	virtual void CreateTerrain() = 0;
	virtual void CreateEnemy(int32 CantidadEnemigos) = 0;
	virtual void CreatePowerUps(int32 CantidadPowerUps) = 0;
	virtual void CreatePortals() = 0;
	virtual void StartPosition() = 0;
	virtual void EndLevel() = 0;
};
