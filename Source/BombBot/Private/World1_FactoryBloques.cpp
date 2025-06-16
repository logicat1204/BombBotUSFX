// Fill out your copyright notice in the Description page of Project Settings.


#include "World1_FactoryBloques.h"
#include "../Bloques/Bloque_Madera.h"
#include "../Bloques/Bloque_Piedra.h"
#include "../Bloques/Bloque_Pasto.h"
#include "../Bloques/Bloque_Tierra.h"
#include "BombBot/Bloques/Bloque_Madera2.h"
#include "BombBot/Bloques/Bloque_Piedra2.h"
#include "BombBot/Bloques/Bloque_Piedra3.h"
#include "BombBot/Bloques/Bloque_Madera3.h"
#include "Bloque_Salida.h"

AActor* AWorld1_FactoryBloques::CrearBloque(FString TypeBlock, FVector Position)
{
	if (TypeBlock == "BloqueMadera")
	{
		Bloque=GetWorld()->SpawnActor<ABloque_Madera>(ABloque_Madera::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloquePiedra")
	{
		Bloque=GetWorld()->SpawnActor<ABloque_Piedra>(ABloque_Piedra::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if(TypeBlock == "BloquePasto")
	{
		Bloque=GetWorld()->SpawnActor<ABloque_Pasto>(ABloque_Pasto::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloqueTierra")
	{
		Bloque=GetWorld()->SpawnActor<ABloque_Tierra>(ABloque_Tierra::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloqueSalida")
	{
		Bloque=GetWorld()->SpawnActor<ABloque_Salida>(ABloque_Salida::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloquePiedra2")
	{
		Bloque = GetWorld()->SpawnActor<ABloque_Piedra2>(ABloque_Piedra2::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloqueMadera2")
	{
		Bloque = GetWorld()->SpawnActor<ABloque_Madera2>(ABloque_Madera2::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloqueMadera3")
	{
		Bloque = GetWorld()->SpawnActor<ABloque_Madera3>(ABloque_Madera3::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else if (TypeBlock == "BloquePiedra3")
	{
		Bloque = GetWorld()->SpawnActor<ABloque_Piedra3>(ABloque_Piedra3::StaticClass(), Position, FRotator::ZeroRotator);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tipo de bloque desconocido: %s"), *TypeBlock);
		return nullptr;
	}

	return Bloque;
}
