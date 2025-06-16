// Fill out your copyright notice in the Description page of Project Settings.


#include "World1_Builder.h"
#include <Kismet/GameplayStatics.h>
#include "BombBotCharacter.h"
// Sets default values
AWorld1_Builder::AWorld1_Builder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWorld1_Builder::BeginPlay()
{
	Super::BeginPlay();
	//CREAMOS LA FABRICA DEL NIVEL
	Factory = GetWorld()->SpawnActor<AWorld1_Factory>(AWorld1_Factory::StaticClass());
	ABombBotCharacter* MiPersonaje = Cast<ABombBotCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MiPersonaje) {
	MiPersonaje->setFabrica(Factory);
	}
}

// Called every frame
void AWorld1_Builder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorld1_Builder::BuildMap()
{
	Factory->CreateMap();
	//Factory->CreateTerrain();
}

void AWorld1_Builder::BuildEnemy(int32 CantidadEnemigos)
{
	Factory->CreateEnemy(CantidadEnemigos);
}

void AWorld1_Builder::BuildPowerUps(int32 CantidadPowerUps)
{
	Factory->CreatePowerUps(CantidadPowerUps);
}

void AWorld1_Builder::BuildPortals()
{
	Factory->CreatePortals();
}

void AWorld1_Builder::SetStartPosition()
{
	Factory->StartPosition();
}

void AWorld1_Builder::FinalizeLevel()
{
	Factory->EndLevel();
}

void AWorld1_Builder::BuildExit()
{
	Factory->CreateExit();
}


