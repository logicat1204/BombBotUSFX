// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/BloqueDestructibleBase.h"
#include "BombBot/Bloques/SubBloqueBase.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABloqueDestructibleBase::ABloqueDestructibleBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        MeshComp->SetStaticMesh(CubeMesh.Object);
    }

    MeshComp->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void ABloqueDestructibleBase::BeginPlay()
{
	Super::BeginPlay();
    DestruirBloque();
    FTimerHandle TimerHandle_Desvanecer;
    GetWorldTimerManager().SetTimer(TimerHandle_Desvanecer, this, &ABloqueDestructibleBase::ActivarDesvanecimientoSubbloques, 4.0f, false);
}

// Called every frame
void ABloqueDestructibleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABloqueDestructibleBase::DestruirBloque()
{
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

                ASubBloqueBase* Fragmento = GetWorld()->SpawnActor<ASubBloqueBase>(ASubBloqueBase::StaticClass(), SpawnLocation, FRotator::ZeroRotator, Params);

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

void ABloqueDestructibleBase::ActivarDesvanecimientoSubbloques()
{
    for (ASubBloqueBase* Fragmento : SubBloquesGuardados)
    {
        if (Fragmento)
        {
            Fragmento->ActivarDesvanecimiento();
        }
    }
}

