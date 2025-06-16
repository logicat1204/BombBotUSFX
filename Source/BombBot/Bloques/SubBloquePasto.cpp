// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/SubBloquePasto.h"

ASubBloquePasto::ASubBloquePasto()
{
    if (MeshComp)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/Bloques_Nuevos/GRASS_BLOCK.GRASS_BLOCK'"));

        if (MaterialBase.Succeeded())
        {
            MeshComp->SetMaterial(0, MaterialBase.Object);
        }
    }
}
