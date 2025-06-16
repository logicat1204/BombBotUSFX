// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveCreditos.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "BombBotCharacter.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ANaveCreditos::ANaveCreditos() // <--- CORREGIDO: APoweUp a APowerUp
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerUpCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PowerUpCollision"));
	PowerUpCollision->SetRelativeScale3D(FVector(50.f,50.f,50.f));
	RootComponent = PowerUpCollision; // <--- MEJORA: Usar RootComponent en vez de SetRootComponent en el constructor es la práctica moderna.

	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUpMesh"));
	PowerUpMesh->SetupAttachment(RootComponent); // <--- MEJORA: Adjuntar al RootComponent es más claro.
	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPowerUp"));
	PowerUpMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaP(TEXT("/Script/Engine.StaticMesh'/Game/AlvaroAssets/Nave_Espacial/Modelo_Nave_Espacial.Modelo_Nave_Espacial'"));

	if (ObjetoMallaP.Succeeded())
	{
		PowerUpMesh->SetStaticMesh(ObjetoMallaP.Object);
		PowerUpMesh->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
		// Desactivar colisión completamente
		PowerUpMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called when the game starts or when spawned
void ANaveCreditos::BeginPlay() // <--- CORREGIDO: APoweUp a APowerUp
{
	Super::BeginPlay();
}

// Called every frame
void ANaveCreditos::Tick(float DeltaTime) // <--- CORREGIDO: APoweUp a APowerUp
{
	Super::Tick(DeltaTime);
}

void ANaveCreditos::NotifyActorBeginOverlap(AActor* OtherActor)
{
	UWorld* World = GetWorld();
	if (!World) return;

	FName NivelActual = *UGameplayStatics::GetCurrentLevelName(World, true);

	int32 IndexActual = ListaNiveles.IndexOfByKey(NivelActual);
	if (IndexActual != INDEX_NONE && IndexActual + 1 < ListaNiveles.Num())
	{
		FName NivelSiguiente = ListaNiveles[IndexActual + 1];
		UGameplayStatics::OpenLevel(World, NivelSiguiente);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hay siguiente nivel o el nivel actual no está en la lista."));
	}
}