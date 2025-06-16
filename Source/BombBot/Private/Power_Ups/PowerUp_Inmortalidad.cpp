// Fill out your copyright notice in the Description page of Project Settings.

#include "Power_Ups/PowerUp_Inmortalidad.h"
#include "BombBotCharacter.h" 
#include "TimerManager.h"     // El header que contiene la funcionalidad de los timers.

APowerUp_Inmortalidad::APowerUp_Inmortalidad()
{

	PrimaryActorTick.bCanEverTick = false;
	MallaPowerUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPowerUp"));
	MallaPowerUp->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaP(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Blender/inmortalidad/inmoBLender.inmoBLender'"));

    if (ObjetoMallaP.Succeeded())
    {
        MallaPowerUp->SetStaticMesh(ObjetoMallaP.Object);
        //MallaPowerUp->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
        // Desactivar colisión completamente
        MallaPowerUp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

bool APowerUp_Inmortalidad::ActivatePowerUp(ABombBotCharacter* PlayerCharacter)
{
    Super::ActivatePowerUp(PlayerCharacter);

    if (PlayerCharacter)
    {
        // Le decimos al personaje que se haga inmortal por un tiempo.
        PlayerCharacter->ActivateImmortality(DuracionInmortalidad);

        // Retornamos true para que la clase base destruya este actor.
        return true;
    }

    return false;
}
