// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Power_Ups/PowerUp.h"
#include "Persona.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBOT_API APersona : public APowerUp
{
	GENERATED_BODY()

public:

	APersona();

protected:

	virtual bool ActivatePowerUp(class ABombBotCharacter* PlayerCharacter) override;


private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MallaPowerUp;
};