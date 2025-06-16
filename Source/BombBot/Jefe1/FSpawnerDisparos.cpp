// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Jefe1/FSpawnerDisparos.h"
#include "BombBotCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AFSpawnerDisparos::AFSpawnerDisparos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFSpawnerDisparos::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFSpawnerDisparos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//Atacamos con esferas pequenias
void AFSpawnerDisparos::Atacar(int32 CantDisparos)
{
	//Obtener posicion actual del jugador
	ABombBotCharacter* Player = Cast<ABombBotCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		FVector SpawnLocation = Player->GetActorLocation();
		FRotator SpawnRotation = Player->GetActorRotation();
		for (int32 i = 0; i < CantDisparos; ++i)
		{
			// Lógica para instanciar el disparo
			// Aquí deberías crear el disparo y establecer su posición y rotación
			// Por ejemplo:
			// GetWorld()->SpawnActor<ADisparo>(DisparoClass, SpawnLocation, SpawnRotation);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No se pudo obtener el jugador para atacar."));
	}
}

