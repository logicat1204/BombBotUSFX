// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Display/HUDPuntuacion.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "BombBotGameInstance.h"
#include "Engine/Engine.h"

AHUDPuntuacion::AHUDPuntuacion()
{
	static ConstructorHelpers::FObjectFinder<UFont> Fuente(TEXT("/Engine/EngineFonts/Roboto"));
	HUDFont = Fuente.Object;
}

void AHUDPuntuacion::DrawHUD()
{
	Super::DrawHUD();
    // Obtener referencia al GameInstance
    UBombBotGameInstance* GameInstance = Cast<UBombBotGameInstance>(GetGameInstance());
    if (GameInstance && HUDFont)
    {
        // Crear texto de puntuación
        FString ScoreText = FString::Printf(TEXT("Puntuacion: %d"), GameInstance->GetScore());

        // Posición en pantalla (esquina superior izquierda)
        float TextX = 50.0f;
        float TextY = 50.0f;

        // Color del texto
        FLinearColor TextColor = FLinearColor::White;

        // Dibujar texto en pantalla
        DrawText(ScoreText, TextColor, TextX, TextY, HUDFont, 1.5f, false);
    }
}

//AHORA DEBEMOS ASIGNAR ESTE HUD EN EL GAMEMODE.
