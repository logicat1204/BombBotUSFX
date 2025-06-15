// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombBotGameMode.h"
#include "BombBotCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

#include "BombBot/Display/HUDPuntuacion.h"

ABombBotGameMode::ABombBotGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> MusicAsset(TEXT("/Script/Engine.SoundWave'/Game/Assets/Musica/Musica_Niveles.Musica_Niveles'"));
	if (MusicAsset.Succeeded())
	{
		LevelMusic = MusicAsset.Object;
	}
}

void ABombBotGameMode::BeginPlay()
{
	Super::BeginPlay();
	// Play the level music
	if (LevelMusic)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), LevelMusic);
	}
	// Optionally, you can set up other game mode specific logic here
	// For example, initializing player stats, setting up the game state, etc.
	// Asignar el HUD personalizado
	HUDClass = AHUDPuntuacion::StaticClass();
}
