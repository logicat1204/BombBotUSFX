// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/Bloque_Madera2.h"

ABloque_Madera2::ABloque_Madera2()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> ObjetoMallaBloque(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/NewBoxAsset/Textures/U_Box4.U_Box4'"));
	if (ObjetoMallaBloque.Succeeded())
	{
		MallaBloque->SetMaterial(0, ObjetoMallaBloque.Object);
	}
}
