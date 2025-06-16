// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWorld_Factory.h"
#include "GameFramework/Actor.h"
#include "World1_Factory.generated.h"

UCLASS()
class BOMBBOT_API AWorld1_Factory : public AActor, public IIWorld_Factory
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorld1_Factory();

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
		{4,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,4},
		{6,5,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,5,6},
		{6,0,4,4,4,1,1,2,4,4,4,2,1,1,4,4,4,0,6},
		{6,1,4,0,0,0,0,0,1,2,1,0,0,0,0,0,4,1,6},
		{6,1,4,0,4,4,4,4,4,4,4,4,4,4,4,0,4,1,6},
		{6,1,0,0,4,0,0,0,1,1,1,0,0,0,4,0,0,1,6},
		{6,2,1,0,4,0,4,4,2,2,2,4,4,0,4,0,1,2,6},
		{6,0,1,0,2,0,4,0,0,0,0,0,4,0,2,0,1,0,6},
		{6,0,4,2,2,2,4,0,2,4,2,0,4,2,2,2,4,0,6},
		{6,0,4,2,1,2,4,2,2,0,2,2,4,2,1,2,4,0,6},
		{6,0,4,2,2,2,4,0,2,4,2,0,4,2,2,2,4,0,6},
		{6,0,1,0,2,0,4,0,0,0,0,0,4,0,2,0,1,0,6},
		{6,2,1,0,4,0,4,4,2,2,2,4,4,0,4,0,1,2,6},
		{6,1,0,0,4,0,0,0,1,1,1,0,0,0,4,0,0,1,6},
		{6,1,4,0,4,4,4,4,4,4,4,4,4,4,4,0,4,1,6},
		{6,1,4,0,0,0,0,0,1,2,1,0,0,0,0,0,4,1,6},
		{6,0,4,4,4,1,1,2,4,4,4,2,1,1,4,4,4,0,6},
		{6,5,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,5,6},
		{4,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,4}
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

	//Metodo para generar una puerta de salida
	void CreateExit();
	TArray<AActor*> TActorBlocks;
	int32 AlturaBloques;
};
