// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "World2_FactoryBloques.generated.h"

UCLASS()
class BOMBBOT_API AWorld2_FactoryBloques : public AActor
{
	GENERATED_BODY()

public:
	void CrearBloque(FString TypeBlock, FVector Position);
};