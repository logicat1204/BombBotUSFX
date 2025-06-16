// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JefeFinal.generated.h"

class AHitboxJefe;
class AFSpawnerDisparos;
class AFSpawnerEscombros;
class AFSpawnerEsbirros;
UCLASS()
class BOMBBOT_API AJefeFinal : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJefeFinal();
	USkeletalMeshComponent* MeshJefe;
	UAnimationAsset* AnimJefeA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JefeFinal")
	AHitboxJefe* HitboxJefe;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 VidaTotal = 15;

	int32 Decision; // 1) Disparos, 2) Escombros, 3) Esbirros
	AFSpawnerDisparos* SpawnerDisparos;
	int32 AttackNums = 3; // Numero de ataques que se realizaran

	AFSpawnerEscombros* SpawnerEscombros;
	int32 EscombrosAttacks = 3;

	AFSpawnerEsbirros* SpawnerEsbirros;
	int32 CantEsbirros = 1;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SpawnHitBox();
	UFUNCTION()
	void DestroyedHitbox(AActor* DestroyedActor);

	void AsignSpawnerDisparos();
	void SpawnSpawnerDisparos();

	void AsignSpawnerEscombros();
	void AttackEscombros();

	void AssignSpawnerEsbirros();
	void SummonEsbirros();

	void DecidirAtaque();

	void DeathEffect();
	//implementacion de un patron facade y sus metodos para el danio al jugador
//Tres formas de atacar
// disparando esferas pequenias hacia el jugador
//Spawneando esbirros que atacan al jugador
//Lanzando escombros encima del jugador que caen y si tocan algo se destruyen, si tocan al jugador le hacen danio
};
