// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Power_Ups/PowerUp.h"
#include "PowerUp_Velocidad.generated.h"
UCLASS()
class BOMBBOT_API APowerUp_Velocidad : public APowerUp
{
	GENERATED_BODY()
	
public:

	APowerUp_Velocidad();

protected:

	virtual bool ActivatePowerUp(class ABombBotCharacter* PlayerCharacter) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	float AumentoVelocidad = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	float DuracionPowerUp = 5.0f;

private:

	FTimerHandle TimerHandle_Velocidad;

	TWeakObjectPtr<ABombBotCharacter> PersonajeAfectado;

	float VelocidadOriginal;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MallaPowerUp;
};
