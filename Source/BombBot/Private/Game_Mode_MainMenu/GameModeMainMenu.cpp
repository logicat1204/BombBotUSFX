// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Mode_MainMenu/GameModeMainMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
AGameModeMainMenu::AGameModeMainMenu()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> MusicAsset(TEXT("/Script/Engine.SoundWave'/Game/Assets/Musica/Main_Menu_Musica.Main_Menu_Musica'"));
	if (MusicAsset.Succeeded())
	{
		LevelMusicM = MusicAsset.Object;
	}
}

void AGameModeMainMenu::BeginPlay()
{
	Super::BeginPlay();
	// Play the level music
	if (LevelMusicM)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), LevelMusicM);
	}
}
