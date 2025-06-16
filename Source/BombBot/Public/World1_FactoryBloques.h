// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactoryBloques.h"
#include "World1_FactoryBloques.generated.h"

UCLASS()
class BOMBBOT_API AWorld1_FactoryBloques : public AFactoryBloques
{
	GENERATED_BODY()
	
public:	
	AActor* CrearBloque(FString TypeBlock, FVector Position);
	
	AActor* Bloque;
};
