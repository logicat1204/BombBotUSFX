// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Bloques/SubBloqueBase.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASubBloqueBase::ASubBloqueBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    // Usa el cubo por defecto
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        MeshComp->SetStaticMesh(CubeMesh.Object);
    }

    MeshComp->SetSimulatePhysics(true);
    MeshComp->SetWorldScale3D(FVector(0.3f)); // fragmentos más pequeños

    // Ajuste para no colisionar con el jugador
    MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MeshComp->SetCollisionResponseToAllChannels(ECR_Block); // Bloquea por defecto
    MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); // Ignora al jugador

    bDestruirSubBloque = false;
    VelocidadEscala = 0.3f; // tamaño inicial
}

// Called when the game starts or when spawned
void ASubBloqueBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASubBloqueBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bDestruirSubBloque)
    {
        VelocidadEscala -= DeltaTime * 0.15f; // reduce escala cada frame

        if (VelocidadEscala <= 0.02f)
        {
            Destroy();
            return;
        }

        MeshComp->SetWorldScale3D(FVector(VelocidadEscala));
    }
}


void ASubBloqueBase::ActivarDesvanecimiento()
{
    bDestruirSubBloque = true;
    MeshComp->SetSimulatePhysics(false); // opcional: congelar mientras se reduce
}
