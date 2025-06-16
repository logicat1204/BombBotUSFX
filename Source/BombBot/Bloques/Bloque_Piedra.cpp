// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque_Piedra.h"
#include "BombBot/Bloques/SubBloquePiedra.h"

ABloque_Piedra::ABloque_Piedra()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/NewBoxAsset/Textures/U_BOX2.U_BOX2'"));

        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object);
        }
    }
}

void ABloque_Piedra::DestruirBloque()
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

                ASubBloqueBase* Fragmento = GetWorld()->SpawnActor<ASubBloquePiedra>(ASubBloquePiedra::StaticClass(), SpawnLocation, FRotator::ZeroRotator, Params);

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
