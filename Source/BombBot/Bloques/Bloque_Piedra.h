// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BloqueGeneral.h"
#include "Bloque_Piedra.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBOT_API ABloque_Piedra : public ABloqueGeneral
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABloque_Piedra();
	void DestruirBloque() override;
};
