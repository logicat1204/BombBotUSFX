// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUps_Factory.h"
#include "Power_Ups/PowerUp_Inmortalidad.h"
#include "Power_Ups/PowerUp_Velocidad.h"
#include "Power_Ups/PoweUp_Curacion.h"

// Sets default values
APowerUps_Factory::APowerUps_Factory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerUps_Factory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUps_Factory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUps_Factory::CreatePowerUp(FVector Location, int PowerUpType)
{
	if (PowerUpType == 1) {
		GetWorld()->SpawnActor<APowerUp_Inmortalidad>(Location, FRotator::ZeroRotator);
	}
	else if (PowerUpType == 2) {
		GetWorld()->SpawnActor<APowerUp_Velocidad>(Location, FRotator::ZeroRotator);
	}
	else if (PowerUpType == 3) {
		GetWorld()->SpawnActor<APoweUp_Curacion>(Location, FRotator::ZeroRotator);
	}
}

