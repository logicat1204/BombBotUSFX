// Fill out your copyright notice in the Description page of Project Settings.


#include "World2_Factory.h"
#include <Kismet/GameplayStatics.h>
#include <Algo/RandomShuffle.h>

#include "Generador_Enemigos.h"

// Sets default values
AWorld2_Factory::AWorld2_Factory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorld2_Factory::BeginPlay()
{
	Super::BeginPlay();
	//Creacion de las fabricas de Bloques
	FabricaBloques = GetWorld()->SpawnActor<AWorld1_FactoryBloques>(AWorld1_FactoryBloques::StaticClass());
}

// Called every frame
void AWorld2_Factory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorld2_Factory::CreateMap()
{
	//Creacion de la parte superior del mapa
	AlturaBloques = 6300.0f;
	CreateBlocks(BasicMap, AlturaBloques);
}

void AWorld2_Factory::CreateTerrain()
{
	//Creacion de la parte inferior del mapa
	AlturaBloques = -200.0f;
	CreateBlocks(TerrainMap, AlturaBloques);
}

void AWorld2_Factory::CreateEnemy(int32 CantidadEnemigos)
{
	MapaCompleto = FullMap(BasicMap);

	// Buscar todas las posiciones libres (valor 0)
	TArray<FIntPoint> PosicionesLibres;
	for (int32 i = 0; i < MapaCompleto.Num(); i++)
	{
		for (int32 j = 0; j < MapaCompleto[i].Num(); j++)
		{
			if (MapaCompleto[i][j] == 0)
			{
				PosicionesLibres.Add(FIntPoint(i, j));
			}
		}
	}

	// Mezclar las posiciones libres para colocar enemigos aleatoriamente
	Algo::RandomShuffle(PosicionesLibres);
	// Limitar la cantidad de enemigos si hay menos espacios libres
	int32 EnemigosAColocar = FMath::Min(CantidadEnemigos, PosicionesLibres.Num());
	/*
	for (int32 i = 0; i < EnemigosAColocar; i++)
	{
		FIntPoint Posicion = PosicionesLibres[i];

		GetWorld()->SpawnActor<ABloqueGeneral>(
			ABloqueGeneral::StaticClass(),
			FVector(Posicion.X * 200.0f, Posicion.Y * 200.0f, 0.0f),
			FRotator::ZeroRotator);
	}
	*/
}

void AWorld2_Factory::CreatePowerUps(int32 CantidadPowerUps)
{
	// Buscar todas las posiciones libres (valor 0)
	TArray<FIntPoint> PosicionesLibres;
	for (int32 i = 0; i < MapaCompleto.Num(); i++)
	{
		for (int32 j = 0; j < MapaCompleto[i].Num(); j++)
		{
			if (MapaCompleto[i][j] == 0)
			{
				PosicionesLibres.Add(FIntPoint(i, j));
			}
		}
	}

	// Mezclar las posiciones libres para colocar los power-ups aleatoriamente
	Algo::RandomShuffle(PosicionesLibres);

	// Limitar la cantidad de power-ups si hay menos espacios libres
	int32 PowerUpsAColocar = FMath::Min(CantidadPowerUps, PosicionesLibres.Num());

	/*
	for (int32 i = 0; i < PowerUpsAColocar; i++)
	{
		FIntPoint Posicion = PosicionesLibres[i];

		// Aquí asumimos que existe una clase llamada APowerUpActor
		GetWorld()->SpawnActor<ABloqueGeneral>(
			ABloqueGeneral::StaticClass(),
			FVector(Posicion.X * 200.0f, Posicion.Y * 200.0f, 0.0f),
			FRotator::ZeroRotator
		);
	}
	*/
}

void AWorld2_Factory::CreatePortals()
{
}

void AWorld2_Factory::StartPosition()
{
	//BUSCAMOS LA POSICION DE INICIO DEL JUGADOR
	int32 filas = BasicMap.Num();
	int32 columnas = BasicMap[0].Num();
	for (int32 i = 0; i < filas; i++)
	{
		for (int32 j = 0; j < columnas; j++)
		{
			if (BasicMap[i][j] == 11)
			{
				// Guardamos la posicion de inicio del jugador
				FVector Posicion = FVector(i * 200.0f, j * 200.0f, 0.0f);
				APawn* jugador = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
				if (jugador)
				{
					jugador->SetActorLocation(Posicion);
				}
			}
		}
	}
}

void AWorld2_Factory::EndLevel()
{
	MapaCompleto.Empty();
	MapaCompleto = FullMap(BasicMap);
	TArray<FVector> Spawns;

	//BUSCAMOS LAS POSICIONES INICIALES
	int32 filas = MapaCompleto.Num();
	int32 columnas = MapaCompleto[0].Num();
	for (int32 i = 0; i < filas; i++)
	{
		for (int32 j = 0; j < columnas; j++)
		{
			if (MapaCompleto[i][j] == 11)
			{
				// Guardamos la posicion de inicio del jugador
				FVector Posicion = FVector(i * 200.0f, j * 200.0f, 0.0f);
				Spawns.Add(Posicion);
			}
		}
	}

	// DEFINIR POSICION FINAL COMO EL SPAWN MÁS LEJANO DEL PRIMERO
	FVector PrimerSpawn = Spawns[0];
	FVector PosicionFinal = PrimerSpawn;
	float DistanciaMaxima = 0.0f;

	for (int32 i = 1; i < Spawns.Num(); i++)
	{
		float Distancia = FVector::Dist(PrimerSpawn, Spawns[i]);
		if (Distancia > DistanciaMaxima)
		{
			DistanciaMaxima = Distancia;
			PosicionFinal = Spawns[i];
		}
	}
	/*
	GetWorld()->SpawnActor<ABloqueGeneral>(
		ABloqueGeneral::StaticClass(),
		PosicionFinal,
		FRotator::ZeroRotator
	);
	*/
}

//METODOS PARA LA CREACION DE MAPA
TArray<TArray<int32>> AWorld2_Factory::FullMap(TArray<TArray<int32>> MapaInicial) {
	int32 filas = MapaInicial.Num();
	int32 columnas = MapaInicial[0].Num();

	int32 newFilas = filas * 2 + 1;
	int32 newColumnas = columnas * 2 + 1;

	// Crear mapa final con espacio para filas y columnas extra (cero)
	TArray<TArray<int32>> MapaFinal;
	MapaFinal.SetNum(newFilas);
	for (int32 i = 0; i < newFilas; i++) {
		MapaFinal[i].SetNum(newColumnas);
		// Inicializar con ceros
		for (int32 j = 0; j < newColumnas; j++) {
			MapaFinal[i][j] = 0;
		}
	}

	// Copiar el mapa original arriba a la izquierda
	for (int32 i = 0; i < filas; i++) {
		for (int32 j = 0; j < columnas; j++) {
			MapaFinal[i][j] = MapaInicial[i][j];
		}
	}

	// Copiar espejo horizontal arriba a la derecha
	for (int32 i = 0; i < filas; i++) {
		for (int32 j = 0; j < columnas; j++) {
			MapaFinal[i][newColumnas - 1 - j] = MapaInicial[i][j];
		}
	}

	// Copiar espejo vertical abajo a la izquierda
	for (int32 i = 0; i < filas; i++) {
		for (int32 j = 0; j < columnas; j++) {
			MapaFinal[newFilas - 1 - i][j] = MapaInicial[i][j];
		}
	}

	// Copiar espejo doble abajo a la derecha
	for (int32 i = 0; i < filas; i++) {
		for (int32 j = 0; j < columnas; j++) {
			MapaFinal[newFilas - 1 - i][newColumnas - 1 - j] = MapaInicial[i][j];
		}
	}

	return MapaFinal;
}


void AWorld2_Factory::CreateBlocks(TArray<TArray<int32>> FullMap, int32 Altura)
{
	if (!FabricaBloques) return;

	const float Espaciado = 200.0f;
	const FVector PuntoInicial = FVector(-1500.0f, -1500.0f, 0.0f);

	int32 Filas = FullMap.Num();
	int32 Columnas = FullMap[0].Num();

	for (int32 i = 0; i < Filas; i++)
	{
		for (int32 j = 0; j < Columnas; j++)
		{
			int32 Tipo = FullMap[i][j];
			FVector Posicion = PuntoInicial + FVector(i * Espaciado, j * Espaciado, AlturaBloques);

			switch (Tipo)
			{
			case 1:
				if (FabricaBloques)
				{
					FabricaBloques->CrearBloque("BloquePasto", Posicion);
				}
				break;

			case 2:
				if (FabricaBloques)
				{
					FabricaBloques->CrearBloque("BloqueMadera", Posicion);
				}
				break;

			case 3:
				if (FabricaBloques)
				{
					FabricaBloques->CrearBloque("BloqueTierra", Posicion);
				}
				break;

			case 4:
				if (FabricaBloques)
				{
					FabricaBloques->CrearBloque("BloquePiedra", Posicion);
				}
				break;
			case 5:
				GetWorld()->SpawnActor<AGenerador_Enemigos>(AGenerador_Enemigos::StaticClass(), Posicion, FRotator::ZeroRotator);
				//verificamos que el enemigo se cree correctamente
				UE_LOG(LogTemp, Warning, TEXT("Enemigo creado en la posicion: %s"), *Posicion.ToString());
				break;
			default:
				break;
			}
		}
	}
}



