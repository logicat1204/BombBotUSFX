// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/Bloque_Piedra3.h"

ABloque_Piedra3::ABloque_Piedra3()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Malla(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/NewBoxAsset/Textures/U_Box7.U_Box7'"));
	if (Malla.Succeeded())
	{
		MallaBloque->SetMaterial(0, Malla.Object);
	}
}
