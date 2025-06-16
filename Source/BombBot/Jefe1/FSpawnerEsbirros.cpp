// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Jefe1/FSpawnerEsbirros.h"
#include "BombBot/Public/Enemigo_Comun.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
AFSpawnerEsbirros::AFSpawnerEsbirros()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Se pone RootComponent para pooder mover al actor con coordenadas.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	/*NUEVO:**Cargar el Blueprint del enemigo desde el constructor
		// Debes reemplazar "Ruta/A_Enemigo_Comun_BP.A_Enemigo_Comun_BP_C'" con la ruta real de tu Blueprint.
		// Para obtener la ruta exacta: en el Content Browser, haz clic derecho en tu Blueprint de enemigo y selecciona "Copy Reference".*/
		static ConstructorHelpers::FObjectFinder<UClass> EnemigoBPClassFinder(TEXT("Class'/Game/Kronos_GHS/Mesh/Basic/Enemigo_Comun.Enemigo_Comun_C'"));
	// Ejemplo de ruta: "Class'/Game/TuCarpeta/TuBlueprintDeEnemigo.TuBlueprintDeEnemigo_C'"

	if (EnemigoBPClassFinder.Succeeded())
	{
		EnemigoBlueprintToSpawn = EnemigoBPClassFinder.Object;
		UE_LOG(LogTemp, Log, TEXT("Blueprint de enemigo cargado exitosamente."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No se pudo encontrar el Blueprint de enemigo en la ruta especificada."));
	}
}

// Called when the game starts or when spawned
void AFSpawnerEsbirros::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFSpawnerEsbirros::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFSpawnerEsbirros::SpawnEsbirros(int32 cant)
{
	for (int32 i = 0; i < cant; i++)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFSpawnerEsbirros::SpawnEsbirro, 1.0f * i, false);
	}
}

void AFSpawnerEsbirros::SpawnEsbirro()
{
    FVector SpawnLocation = GetActorLocation();
	float randomX = FMath::RandRange(-500.0f, 500.0f);
	float randomY = FMath::RandRange(-500.0f, 500.0f);
    SpawnLocation.Z += 100.0f;
	SpawnLocation.X += randomX;
	SpawnLocation.Y += randomY;
    FRotator SpawnRotation = GetActorRotation();

    // Usa EnemigoBlueprintToSpawn si se cargó correctamente
    if (EnemigoBlueprintToSpawn)
    {
        AEnemigo_Comun* SpawnedEnemy = GetWorld()->SpawnActor<AEnemigo_Comun>(EnemigoBlueprintToSpawn, SpawnLocation, SpawnRotation);

        if (!SpawnedEnemy)
        {
            UE_LOG(LogTemp, Warning, TEXT("No se pudo spawnear el enemigo. Posiblemente por problemas de colision o Blueprint no valido."));
            return;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("El Blueprint de enemigo no se pudo cargar. Asegurate de que la ruta en el constructor es correcta."));
    }
}

