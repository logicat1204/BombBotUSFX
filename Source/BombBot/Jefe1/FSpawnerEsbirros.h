// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FSpawnerEsbirros.generated.h"

class AEnemigo_Comun;
UCLASS()
class BOMBBOT_API AFSpawnerEsbirros : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFSpawnerEsbirros();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnEsbirros(int32 cant);
	void SpawnEsbirro();

	// **NUEVO:** Variable privada para almacenar la clase Blueprint cargada
	UPROPERTY(EditDefaultsOnly, Category = "Enemigos")
	TSubclassOf<AEnemigo_Comun> EnemigoBlueprintToSpawn;
};
