// Fill out your copyright notice in the Description page of Project Settings.


#include "World2_Builder.h"
#include "World2_Factory.h"

// Sets default values
AWorld2_Builder::AWorld2_Builder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorld2_Builder::BeginPlay()
{
	Super::BeginPlay();
	Factory = GetWorld()->SpawnActor<AWorld2_Factory>(AWorld2_Factory::StaticClass());
}

// Called every frame
void AWorld2_Builder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorld2_Builder::BuildMap()
{
	Factory->CreateMap();
	//Factory->CreateTerrain();
}

void AWorld2_Builder::BuildEnemy(int32 CantidadEnemigos)
{
	Factory->CreateEnemy(CantidadEnemigos);
}

void AWorld2_Builder::BuildPowerUps(int32 CantidadPowerUps)
{
	Factory->CreatePowerUps(CantidadPowerUps);
}

void AWorld2_Builder::BuildPortals()
{
	Factory->CreatePortals();
}

void AWorld2_Builder::SetStartPosition()
{
	Factory->StartPosition();
}

void AWorld2_Builder::FinalizeLevel()
{
	Factory->EndLevel();
}

