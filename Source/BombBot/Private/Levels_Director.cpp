// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels_Director.h"

// Sets default values
ALevels_Director::ALevels_Director()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevels_Director::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevels_Director::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevels_Director::SetLevelBuilder(AActor* Builder)
{
	//Casteo de Builder a LevelBuilder
	LevelBuilder = Cast<IILevels_Builder>(Builder);
}

void ALevels_Director::CreateLevel1()
{
	LevelBuilder->BuildMap();
	LevelBuilder->BuildEnemy(5);
	LevelBuilder->BuildPowerUps(5);
	LevelBuilder->BuildPortals();
	LevelBuilder->SetStartPosition();
	LevelBuilder->FinalizeLevel();
}

void ALevels_Director::CreateLevel2()
{
	LevelBuilder->BuildMap();
	LevelBuilder->BuildEnemy(5);
	LevelBuilder->BuildPowerUps(5);
	LevelBuilder->BuildPortals();
	LevelBuilder->SetStartPosition();
	LevelBuilder->FinalizeLevel();
}

void ALevels_Director::CreateLevel3()
{
	LevelBuilder->BuildMap();
	LevelBuilder->BuildEnemy(5);
	LevelBuilder->BuildPowerUps(5);
	LevelBuilder->BuildPortals();
	LevelBuilder->SetStartPosition();
	LevelBuilder->FinalizeLevel();
}

void ALevels_Director::CreateLevel4()
{
	LevelBuilder->BuildMap();
	LevelBuilder->BuildEnemy(5);
	LevelBuilder->BuildPowerUps(5);
	LevelBuilder->BuildPortals();
	LevelBuilder->SetStartPosition();
	LevelBuilder->FinalizeLevel();
}

void ALevels_Director::CreateLevel5()
{
	LevelBuilder->BuildMap();
	LevelBuilder->BuildEnemy(5);
	LevelBuilder->BuildPowerUps(5);
	LevelBuilder->BuildPortals();
	LevelBuilder->SetStartPosition();
	LevelBuilder->FinalizeLevel();
}

void ALevels_Director::CreateLevel6()
{
}

void ALevels_Director::CreateLevel7()
{
}

void ALevels_Director::CreateLevel8()
{
}

void ALevels_Director::CreateLevel9()
{
}

void ALevels_Director::CreateLevel10()
{
}



