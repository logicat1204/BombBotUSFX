// Fill out your copyright notice in the Description page of Project Settings.


#include "World1_FactoryBloques.h"
#include "../Bloques/Bloque_Madera.h"
#include "../Bloques/Bloque_Piedra.h"
#include "../Bloques/Bloque_Pasto.h"
#include "../Bloques/Bloque_Tierra.h"

void AWorld1_FactoryBloques::CrearBloque(FString TypeBlock, FVector Position)
{
	if (TypeBlock == "BloqueMadera")
	{
		GetWorld()->SpawnActor<ABloque_Madera>(ABloque_Madera::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloquePiedra")
	{
		GetWorld()->SpawnActor<ABloque_Piedra>(ABloque_Piedra::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if(TypeBlock == "BloquePasto")
	{
		GetWorld()->SpawnActor<ABloque_Pasto>(ABloque_Pasto::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloqueTierra")
	{
		GetWorld()->SpawnActor<ABloque_Tierra>(ABloque_Tierra::StaticClass(), Position, FRotator::ZeroRotator);
	}
}
