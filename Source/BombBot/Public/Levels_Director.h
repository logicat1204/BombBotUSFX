// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ILevels_Builder.h"
#include "GameFramework/Actor.h"
#include "Levels_Director.generated.h"

UCLASS()
class BOMBBOT_API ALevels_Director : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevels_Director();

	IILevels_Builder* LevelBuilder;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Asignar el builder de niveles
	void SetLevelBuilder(AActor* Builder);

	//Creacion de niveles
	void CreateLevel1();
	void CreateLevel2();
	void CreateLevel3();
	void CreateLevel4();
	void CreateLevel5();
	void CreateLevel6();
	void CreateLevel7();
	void CreateLevel8();
	void CreateLevel9();
	void CreateLevel10();
};
