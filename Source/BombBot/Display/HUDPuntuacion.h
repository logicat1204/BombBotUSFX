// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDPuntuacion.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBOT_API AHUDPuntuacion : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUDPuntuacion();

protected:
	virtual void DrawHUD() override;

private:
	//fuente para el texto
	UPROPERTY()
	class UFont* HUDFont;
};
