// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/Bloque_Madera3.h"

ABloque_Madera3::ABloque_Madera3()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Malla(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/NewBoxAsset/Textures/U_Box6.U_Box6'"));
	if (Malla.Succeeded())
	{
		MallaBloque->SetMaterial(0,Malla.Object);
	}
}
