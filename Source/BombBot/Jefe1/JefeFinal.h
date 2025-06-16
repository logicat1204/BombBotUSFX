// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JefeFinal.generated.h"

class AHitboxJefe;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SpawnHitBox();
	UFUNCTION()
	void DestroyedHitbox(AActor* DestroyedActor);

	//implementacion de un patron facade y sus metodos para el danio al jugador
//Tres formas de atacar
// disparando esferas pequenias hacia el jugador
//Spawneando esbirros que atacan al jugador
//Lanzando escombros encima del jugador que caen y si tocan algo se destruyen, si tocan al jugador le hacen danio
};
