// Fill out your copyright notice in the Description page of Project Settings.

#include "Power_Ups/PowerUp_Velocidad.h"
#include "BombBotCharacter.h"
#include "GameFramework/CharacterMovementComponent.h" // Necesario para cambiar la velocidad


APowerUp_Velocidad::APowerUp_Velocidad()
{

	PrimaryActorTick.bCanEverTick = false;
    MallaPowerUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPowerUp"));
    MallaPowerUp->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaP(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Blender/Velocidad/velMallaJunto.velMallaJunto'"));

    if (ObjetoMallaP.Succeeded())
    {
        MallaPowerUp->SetStaticMesh(ObjetoMallaP.Object);
        MallaPowerUp->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
        // Desactivar colisión completamente
        MallaPowerUp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

bool APowerUp_Velocidad::ActivatePowerUp(ABombBotCharacter* PlayerCharacter)
{
    Super::ActivatePowerUp(PlayerCharacter);

    if (PlayerCharacter)
    {
        // Simplemente le decimos al personaje que active su propio efecto.
        PlayerCharacter->ActivateSpeedBoost(AumentoVelocidad, DuracionPowerUp);

        // Retornamos true para que la clase base destruya este actor.
        return true;
    }

    return false;
}
