// Fill out your copyright notice in the Description page of Project Settings.


#include "Personas/Persona.h"

// PowerUp_Velocidad.cpp
// Fill out your copyright notice in the Description page of Project Settings.

#include "BombBotCharacter.h"

APersona::APersona()
{

    PrimaryActorTick.bCanEverTick = false;
    MallaPowerUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPowerUp"));
    MallaPowerUp->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaP(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Blender/Velocidad/velMallaJunto.velMallaJunto'"));

    if (ObjetoMallaP.Succeeded())
    {
        MallaPowerUp->SetStaticMesh(ObjetoMallaP.Object);
        MallaPowerUp->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
    }
}

bool APersona::ActivatePowerUp(ABombBotCharacter* PlayerCharacter)
{
    Super::ActivatePowerUp(PlayerCharacter);

    if (PlayerCharacter)
    {
        PlayerCharacter->OpenEscapeDoor();

        return true;
    }

    return false;
}