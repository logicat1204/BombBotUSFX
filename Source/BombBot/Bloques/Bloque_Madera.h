// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BloqueGeneral.h"
#include "BombBot/Bloques/BloqueDestructibleBase.h"
#include "Bloque_Madera.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBOT_API ABloque_Madera : public ABloqueGeneral
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABloque_Madera();
	
	void DestruirBloque() override;
};
