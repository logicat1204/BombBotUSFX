// Fill out your copyright notice in the Description page of Project Settings.


#include "Generador_Enemigos.h"
#include "Enemigo_Comun.h"

// Sets default values
AGenerador_Enemigos::AGenerador_Enemigos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObject(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));

	if (MeshObject.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObject.Object);
		Mesh->SetWorldScale3D(FVector(0.5f, 0.5f, 2.0f));
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}

}

// Called when the game starts or when spawned
void AGenerador_Enemigos::BeginPlay()
{
	Super::BeginPlay();
	//Generamos enemigos cada cierto tiempo
	GetWorldTimerManager().SetTimer(TimerHandle_EnemySpawn, this, &AGenerador_Enemigos::SpawnEnemy, SpawnInterval, true, PreSpawnTime);
}

// Called every frame
void AGenerador_Enemigos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGenerador_Enemigos::SpawnEnemy()
{
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z += 100.0f; // Ajustar la altura de aparición del enemigo
	FRotator SpawnRotation = GetActorRotation();
	AEnemigo_Comun* SpawnedEnemy = GetWorld()->SpawnActor<AEnemigo_Comun>(AEnemigo_Comun::StaticClass(), SpawnLocation, SpawnRotation);
}

