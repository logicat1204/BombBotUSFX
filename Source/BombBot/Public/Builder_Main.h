// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World1_Builder.h"
#include "Levels_Director.h"
#include "GameFramework/Actor.h"
#include "Builder_Main.generated.h"

UCLASS()
class BOMBBOT_API ABuilder_Main : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilder_Main();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//CREAMOS AL BUILDER Y AL DIRECTOR
	AWorld1_Builder* Builder;
	ALevels_Director* Director;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
