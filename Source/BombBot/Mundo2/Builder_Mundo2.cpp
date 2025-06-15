// Fill out your copyright notice in the Description page of Project Settings.


#include "Builder_Mundo2.h"
#include "Levels_Director.h"
#include "World2_Builder.h"

// Sets default values
ABuilder_Mundo2::ABuilder_Mundo2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuilder_Mundo2::BeginPlay()
{
	Super::BeginPlay();
	Director = GetWorld()->SpawnActor<ALevels_Director>(ALevels_Director::StaticClass());
	Builder = GetWorld()->SpawnActor<AWorld2_Builder>(AWorld2_Builder::StaticClass());

	Builder->BuildMap();
}

// Called every frame
void ABuilder_Mundo2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

