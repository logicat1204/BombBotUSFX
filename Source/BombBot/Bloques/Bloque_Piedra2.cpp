// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/Bloque_Piedra2.h"

ABloque_Piedra2::ABloque_Piedra2()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> AssetMesh(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/NewBoxAsset/Textures/U_Box5.U_Box5'"));
	if (AssetMesh.Succeeded())
	{
		MallaBloque->SetMaterial(0, AssetMesh.Object);
	}
}
