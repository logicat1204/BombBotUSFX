// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/SubBloquePiedra.h"

ASubBloquePiedra::ASubBloquePiedra()
{
    if (MeshComp)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Rock_Marble_Polished.M_Rock_Marble_Polished'"));

        if (MaterialBase.Succeeded())
        {
            MeshComp->SetMaterial(0, MaterialBase.Object);
        }
    }
}
