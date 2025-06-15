// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque_Tierra.h"

ABloque_Tierra::ABloque_Tierra()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/LevelPrototyping/Materials/Level1/Ground048_2K-JPG/M_DirtFloor.M_DirtFloor'"));

        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object);
        }
    }
}