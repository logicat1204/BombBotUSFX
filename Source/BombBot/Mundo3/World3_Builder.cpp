// Fill out your copyright notice in the Description page of Project Settings.


#include "World3_Builder.h"
#include "World3_Factory.h"

// Sets default values
AWorld3_Builder::AWorld3_Builder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorld3_Builder::BeginPlay()
{
	Super::BeginPlay();
	Factory = GetWorld()->SpawnActor<AWorld3_Factory>(AWorld3_Factory::StaticClass());
}

// Called every frame
void AWorld3_Builder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorld3_Builder::BuildMap()
{
	Factory->CreateMap();
	//Factory->CreateTerrain();
}

void AWorld3_Builder::BuildEnemy(int32 CantidadEnemigos)
{
	Factory->CreateEnemy(CantidadEnemigos);
}

void AWorld3_Builder::BuildPowerUps(int32 CantidadPowerUps)
{
	Factory->CreatePowerUps(CantidadPowerUps);
}

void AWorld3_Builder::BuildPortals()
{
	Factory->CreatePortals();
}

void AWorld3_Builder::SetStartPosition()
{
	Factory->StartPosition();
}

void AWorld3_Builder::FinalizeLevel()
{
	Factory->EndLevel();
}
