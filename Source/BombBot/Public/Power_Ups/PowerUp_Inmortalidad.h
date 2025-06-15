// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Power_Ups/PowerUp.h"
#include "PowerUp_Inmortalidad.generated.h"
UCLASS()
class BOMBBOT_API APowerUp_Inmortalidad : public APowerUp
{
	GENERATED_BODY()
	
public:

	APowerUp_Inmortalidad();

protected:

	virtual bool ActivatePowerUp(class ABombBotCharacter* PlayerCharacter) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	float DuracionInmortalidad = 5.0f; // Duración

private:

	FTimerHandle TimerHandle_Inmortalidad;

	TWeakObjectPtr<class ABombBotCharacter> PersonajeAfectado;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MallaPowerUp;
};
