// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWorld_Factory.h"
#include "GameFramework/Actor.h"
#include "World2_Factory.generated.h"

UCLASS()
class BOMBBOT_API AWorld2_Factory : public AActor, public IIWorld_Factory
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorld2_Factory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Implement the CreateLevel method from IILevelFactory interface
	virtual void CreateMap() override;
	virtual void CreateTerrain() override;
	virtual void CreateEnemy(int32 CantidadEnemigos) override;
	virtual void CreatePowerUps(int32 CantidadPowerUps) override;
	virtual void CreatePortals() override;
	virtual void StartPosition() override;
	virtual void EndLevel() override;

	//MAPA PRINCIPAL Y METODOS AUXILIARES
	//Mapa de Bloques
	TArray<TArray<int32>> BasicMap = {
		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
		{4,5,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,5,4},
		{4,0,4,4,4,1,1,2,4,4,4,2,1,1,4,4,4,0,4},
		{4,1,4,0,0,0,0,0,1,2,1,0,0,0,0,0,4,1,4},
		{4,1,4,0,4,4,4,4,4,4,4,4,4,4,4,0,4,1,4},
		{4,1,0,0,4,0,0,0,1,1,1,0,0,0,4,0,0,1,4},
		{4,2,1,0,4,0,4,4,2,2,2,4,4,0,4,0,1,2,4},
		{4,0,1,0,2,0,4,0,0,0,0,0,4,0,2,0,1,0,4},
		{4,0,4,2,2,2,4,0,2,4,2,0,4,2,2,2,4,0,4},
		{4,0,4,2,1,2,4,2,2,0,2,2,4,2,1,2,4,0,4},
		{4,0,4,2,2,2,4,0,2,4,2,0,4,2,2,2,4,0,4},
		{4,0,1,0,2,0,4,0,0,0,0,0,4,0,2,0,1,0,4},
		{4,2,1,0,4,0,4,4,2,2,2,4,4,0,4,0,1,2,4},
		{4,1,0,0,4,0,0,0,1,1,1,0,0,0,4,0,0,1,4},
		{4,1,4,0,4,4,4,4,4,4,4,4,4,4,4,0,4,1,4},
		{4,1,4,0,0,0,0,0,1,2,1,0,0,0,0,0,4,1,4},
		{4,0,4,4,4,1,1,2,4,4,4,2,1,1,4,4,4,0,4},
		{4,5,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,5,4},
		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
	};

	//Mapa del terreno
	TArray<TArray<int32>> TerrainMap = {
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
	};


	TArray<TArray<int32>> MapaCompleto;
	TArray<TArray<int32>> FullMap(TArray<TArray<int32>> MapaInicial);
	void CreateBlocks(TArray<TArray<int32>> FullMap, int32 Altura);

	int32 AlturaBloques;
};
