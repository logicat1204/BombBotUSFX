// Fill out your copyright notice in the Description page of Project Settings.


#include "World2_FactoryBloques.h"
#include "../Bloques/Bloque_Madera.h"
#include "../Bloques/Bloque_Piedra.h"
#include "../Bloques/Bloque_Pasto.h"
#include "../Bloques/Bloque_Tierra.h"

void AWorld2_FactoryBloques::CrearBloque(FString TypeBlock, FVector Position)
{
	if (TypeBlock == "BloqueMadera2")
	{
		GetWorld()->SpawnActor<ABloque_Madera>(ABloque_Madera::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloquePiedra2")
	{
		GetWorld()->SpawnActor<ABloque_Piedra>(ABloque_Piedra::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloquePasto2")
	{
		GetWorld()->SpawnActor<ABloque_Pasto>(ABloque_Pasto::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloqueTierra2")
	{
		GetWorld()->SpawnActor<ABloque_Tierra>(ABloque_Tierra::StaticClass(), Position, FRotator::ZeroRotator);
	}
}


