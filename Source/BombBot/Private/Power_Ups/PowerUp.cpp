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
	RootComponent = PowerUpCollision; // <--- MEJORA: Usar RootComponent en vez de SetRootComponent en el constructor es la práctica moderna.

	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUpMesh"));
	PowerUpMesh->SetupAttachment(RootComponent); // <--- MEJORA: Adjuntar al RootComponent es más claro.

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

	// Hacemos un Cast para ver si el actor que colisionó es nuestro personaje.
	ABombBotCharacter* PlayerCharacter = Cast<ABombBotCharacter>(OtherActor);

	// Si el Cast falla (es decir, colisionó con algo que no es el personaje), no hacemos nada.
	if (!PlayerCharacter)
	{
		return;
	}

	// Llamamos a la función virtual y le pasamos el personaje que recogió el Power-Up.
	if (ActivatePowerUp(PlayerCharacter)) // <--- LÓGICA MEJORADA
	{
		// Si el power-up se activó correctamente, destruimos el actor del power-up.
		Destroy();
	}
}

// LÓGICA MEJORADA: La función ahora acepta el personaje como parámetro.
// Esto hace que el código sea mucho más limpio y reutilizable.
bool APowerUp::ActivatePowerUp(ABombBotCharacter* PlayerCharacter)
{
	// Esta es la implementación base. Las clases que hereden de esta
	// (ej: APowerUp_SpeedBoost) sobreescribirán esta función.

	// Si el puntero al personaje es válido...
	if (PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Power Up base activado por %s. Esta función debe ser sobreescrita."), *PlayerCharacter->GetName());
		return true; // <--- CORREGIDO: Debería retornar true si se "activa" con éxito.
	}

	return false;
}