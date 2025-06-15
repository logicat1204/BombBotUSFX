// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Power_Ups/PowerUp.h"
#include "GameFramework/Actor.h"
#include "PoweUp_Curacion.generated.h"
UCLASS()
class BOMBBOT_API APoweUp_Curacion : public APowerUp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoweUp_Curacion();

protected:

	virtual bool ActivatePowerUp(class ABombBotCharacter* PlayerCharacter) override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	int32 CantidadCuracion = 1;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MallaPowerUp;
};