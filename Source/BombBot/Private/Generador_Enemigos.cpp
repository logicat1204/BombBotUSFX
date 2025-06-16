// Fill out your copyright notice in the Description page of Project Settings.


#include "Generador_Enemigos.h"
#include "Enemigo_Comun.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

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
    
    // **NUEVO:** Cargar el Blueprint del enemigo desde el constructor
        // Debes reemplazar "Ruta/A_Enemigo_Comun_BP.A_Enemigo_Comun_BP_C'" con la ruta real de tu Blueprint.
        // Para obtener la ruta exacta: en el Content Browser, haz clic derecho en tu Blueprint de enemigo y selecciona "Copy Reference".
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
    SpawnLocation.Z += 100.0f;
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

        cont_Enemigos++;

        if (cont_Enemigos >= 3)
        {
            UCharacterMovementComponent* Movement = SpawnedEnemy->GetCharacterMovement();
            if (Movement)
            {
                Movement->MaxWalkSpeed = 400.0f;
            }
            else
            {
                // Log si el enemigo spawneado no tiene un CharacterMovementComponent
                UE_LOG(LogTemp, Warning, TEXT("El enemigo spawneado no tiene un CharacterMovementComponent. No se pudo cambiar la velocidad."));
                return;
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("El Blueprint de enemigo no se pudo cargar. Asegúrate de que la ruta en el constructor es correcta."));
    }
}


