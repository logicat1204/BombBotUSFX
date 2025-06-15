// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BloqueGeneral.h"
#include "Bloque_Pasto.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBOT_API ABloque_Pasto : public ABloqueGeneral
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABloque_Pasto();
	void DestruirBloque() override;
};
