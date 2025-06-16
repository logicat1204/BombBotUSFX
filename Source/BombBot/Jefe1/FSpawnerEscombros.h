// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FSpawnerEscombros.generated.h"

class ABombBotCharacter;
UCLASS()
class BOMBBOT_API AFSpawnerEscombros : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFSpawnerEscombros();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	ABombBotCharacter* Player;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AtacarES(int32 CantDisparos);
	void SpawnAtack();
};
