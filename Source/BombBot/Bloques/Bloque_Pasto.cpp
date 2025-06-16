// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque_Pasto.h"
#include "BombBot/Bloques/SubBloquePasto.h"
ABloque_Pasto::ABloque_Pasto()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaHija(TEXT("/Script/Engine.StaticMesh'/Game/AlvaroAssets/Bloques_Nuevos/Sin_nombre.Sin_nombre'"));
    if (MallaHija.Succeeded())
    {
        MallaBloque->SetStaticMesh(MallaHija.Object);
		MallaBloque->SetWorldScale3D(FVector(0.53f, 0.53f, 0.53f));
    }
  
}

void ABloque_Pasto::DestruirBloque()
{
    FTimerHandle TimerHandle_Desvanecer;
    GetWorldTimerManager().SetTimer(TimerHandle_Desvanecer, this, &ABloqueGeneral::ActivarDesvanecimientoSubbloques, 4.0f, false);

    FVector Origin = GetActorLocation();

    // Oculta el original
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    // Fragmenta en 8 cubos pequeños (2x2x2)
    for (int x = 0; x < 2; ++x)
    {
        for (int y = 0; y < 2; ++y)
        {
            for (int z = 0; z < 2; ++z)
            {
                FVector Offset(x * 30.f, y * 30.f, z * 30.f);
                FVector SpawnLocation = Origin + Offset;

                FActorSpawnParameters Params;
                Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                ASubBloqueBase* Fragmento = GetWorld()->SpawnActor<ASubBloquePasto>(ASubBloquePasto::StaticClass(), SpawnLocation, FRotator::ZeroRotator, Params);

                if (Fragmento)
                {
                    // Aplica impulso aleatorio para simular explosión
                    FVector Impulso = FVector(FMath::RandRange(-200, 2000), FMath::RandRange(-200, 2000), FMath::RandRange(500, 2000));
                    Fragmento->FindComponentByClass<UStaticMeshComponent>()->AddImpulse(Impulso);
                    SubBloquesGuardados.Add(Fragmento);
                }
            }
        }
    }

    // Destruye el actor original después de 1 segundo
    SetLifeSpan(5.0f);
}

