// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/SubBloquePasto.h"

ASubBloquePasto::ASubBloquePasto()
{
    if (MeshComp)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/LevelPrototyping/Materials/Level1/Grass008_2K-PNG/M_Grass2.M_Grass2'"));

        if (MaterialBase.Succeeded())
        {
            MeshComp->SetMaterial(0, MaterialBase.Object);
        }
    }
}
