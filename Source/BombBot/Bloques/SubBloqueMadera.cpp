// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/SubBloqueMadera.h"

ASubBloqueMadera::ASubBloqueMadera() 
{
    if (MeshComp)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));

        if (MaterialBase.Succeeded())
        {
            MeshComp->SetMaterial(0, MaterialBase.Object);
        }
    }
}