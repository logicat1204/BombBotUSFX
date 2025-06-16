// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueGeneral.h"
#include "BombBot/Bloques/SubBloqueBase.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABloqueGeneral::ABloqueGeneral()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaBloque = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBloque"));
	MallaBloque->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaBloque(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (ObjetoMallaBloque.Succeeded())
	{
		MallaBloque->SetStaticMesh(ObjetoMallaBloque.Object);
		MallaBloque->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	}

	MallaBloque->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void ABloqueGeneral::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABloqueGeneral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(estado==1&&durabilidad==0)
    {
        estado = 0;
        DestruirBloque();
    }
}

void ABloqueGeneral::DestruirBloque()
{
    /*
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
    */
}

void ABloqueGeneral::ActivarDesvanecimientoSubbloques()
{
    for (ASubBloqueBase* Fragmento : SubBloquesGuardados)
    {
        if (Fragmento)
        {
            Fragmento->ActivarDesvanecimiento();
        }
    }
}

void ABloqueGeneral::Impactar()
{
    if (durabilidad > 0) {
        durabilidad--;
    }
}