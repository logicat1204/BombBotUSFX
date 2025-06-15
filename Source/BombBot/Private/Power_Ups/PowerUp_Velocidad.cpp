// Fill out your copyright notice in the Description page of Project Settings.


#include "Power_Ups/PowerUp_Velocidad.h"

// Sets default values
APowerUp_Velocidad::APowerUp_Velocidad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerUp_Velocidad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUp_Velocidad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

