#include "Enemigos/Enemigo.h"

bool AEnemigo::bJugadorDetectado = true;
FTimerHandle AEnemigo::TimerReiniciarDeteccion;

AEnemigo::AEnemigo()
{
    PrimaryActorTick.bCanEverTick = true;

}

void AEnemigo::BeginPlay()
{
    Super::BeginPlay();

}

void AEnemigo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}