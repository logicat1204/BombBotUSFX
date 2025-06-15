// Fill out your copyright notice in the Description page of Project Settings.


#include "Builder_Main.h"

// Sets default values
ABuilder_Main::ABuilder_Main()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuilder_Main::BeginPlay()
{
	Super::BeginPlay();
	//SPAWN DEL BUILDER Y EL DIRECTOR
	Builder = GetWorld()->SpawnActor<AWorld1_Builder>(AWorld1_Builder::StaticClass());
	Director = GetWorld()->SpawnActor<ALevels_Director>(ALevels_Director::StaticClass());

	Director->SetLevelBuilder(Builder);
	Builder->BuildMap();

}

// Called every frame
void ABuilder_Main::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

