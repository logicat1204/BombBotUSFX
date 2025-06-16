// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo_Comun.h"
#include "Generador_Enemigos.generated.h"

UCLASS()
class BOMBBOT_API AGenerador_Enemigos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerador_Enemigos();

	UStaticMeshComponent* Mesh; // Componente de malla estática para el generador de enemigos

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemy();// Funcion para generar enemigos

	FTimerHandle TimerHandle_EnemySpawn; //Ter para controlar el spawn de enemigos
	float SpawnInterval = 5.0f; // Intervalo de tiempo entre spawns
	float PreSpawnTime = 5.f; // Tiempo de pre-spawn antes de que el enemigo aparezca
	float cont_Enemigos = 0;
    
    // **NUEVO:** Variable privada para almacenar la clase Blueprint cargada
    UPROPERTY(EditDefaultsOnly, Category = "Enemigos")
    TSubclassOf<AEnemigo_Comun> EnemigoBlueprintToSpawn;
};
