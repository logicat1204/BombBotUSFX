// Fill out your copyright notice in the Description page of Project Settings.


#include "World1_FactoryBloques.h"
#include "../Bloques/Bloque_Madera.h"
#include "../Bloques/Bloque_Piedra.h"
#include "../Bloques/Bloque_Pasto.h"
#include "../Bloques/Bloque_Tierra.h"
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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tipo de bloque desconocido: %s"), *TypeBlock);
		return nullptr;
	}

	return Bloque;
}
