// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Jefe1/FSpawnerDisparos.h"
#include "BombBotCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BombBot/Jefe1/FDisparo.h"

// Sets default values
AFSpawnerDisparos::AFSpawnerDisparos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
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
	for (int32 i = 0; i <= CantDisparos; i++)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFSpawnerDisparos::SpawnAtack, 1.0f * i, false);
	}
}

void AFSpawnerDisparos::SpawnAtack()
{
	// Spawn the projectile actor
	AFDisparo* Disparo = GetWorld()->SpawnActor<AFDisparo>(AFDisparo::StaticClass(), GetActorLocation(), GetActorRotation());
}

