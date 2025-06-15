// Fill out your copyright notice in the Description page of Project Settings.

#include "Power_Ups/PowerUp.h" // <--- CORREGIDO: PoweUp.h a PowerUp.h (debe coincidir con el nombre de tu archivo)
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "BombBotCharacter.h"


// Sets default values
APowerUp::APowerUp() // <--- CORREGIDO: APoweUp a APowerUp
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerUpCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PowerUpCollision"));
	RootComponent = PowerUpCollision; // <--- MEJORA: Usar RootComponent en vez de SetRootComponent en el constructor es la pr�ctica moderna.

	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUpMesh"));
	PowerUpMesh->SetupAttachment(RootComponent); // <--- MEJORA: Adjuntar al RootComponent es m�s claro.

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay() // <--- CORREGIDO: APoweUp a APowerUp
{
	Super::BeginPlay();
}

// Called every frame
void APowerUp::Tick(float DeltaTime) // <--- CORREGIDO: APoweUp a APowerUp
{
	Super::Tick(DeltaTime);
}

void APowerUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Hacemos un Cast para ver si el actor que colision� es nuestro personaje.
	ABombBotCharacter* PlayerCharacter = Cast<ABombBotCharacter>(OtherActor);

	// Si el Cast falla (es decir, colision� con algo que no es el personaje), no hacemos nada.
	if (!PlayerCharacter)
	{
		return;
	}

	// Llamamos a la funci�n virtual y le pasamos el personaje que recogi� el Power-Up.
	if (ActivatePowerUp(PlayerCharacter)) // <--- L�GICA MEJORADA
	{
		// Si el power-up se activ� correctamente, destruimos el actor del power-up.
		Destroy();
	}
}

// L�GICA MEJORADA: La funci�n ahora acepta el personaje como par�metro.
// Esto hace que el c�digo sea mucho m�s limpio y reutilizable.
bool APowerUp::ActivatePowerUp(ABombBotCharacter* PlayerCharacter)
{
	// Esta es la implementaci�n base. Las clases que hereden de esta
	// (ej: APowerUp_SpeedBoost) sobreescribir�n esta funci�n.

	// Si el puntero al personaje es v�lido...
	if (PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Power Up base activado por %s. Esta funci�n debe ser sobreescrita."), *PlayerCharacter->GetName());
		return true; // <--- CORREGIDO: Deber�a retornar true si se "activa" con �xito.
	}

	return false;
}