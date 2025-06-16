// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Jefe1/FEscombro.h"
#include "Kismet/GameplayStatics.h"
#include "BombBotCharacter.h"

// Sets default values
AFEscombro::AFEscombro()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaDisparo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaDisparo"));
	RootComponent = MallaDisparo;

	// No activar física inmediatamente - se activará en BeginPlay
	MallaDisparo->SetSimulatePhysics(false);
	MallaDisparo->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	MallaDisparo->SetNotifyRigidBodyCollision(true);

	// Desactivar gravedad para proyectiles
	MallaDisparo->SetEnableGravity(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MeshAsset.Succeeded())
	{
		MallaDisparo->SetStaticMesh(MeshAsset.Object);
		MallaDisparo->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
		MallaDisparo->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MallaDisparo->SetCollisionResponseToAllChannels(ECR_Block);
		MallaDisparo->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No se pudo cargar el mesh de disparo"));
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialEsc(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Rock_Sandstone.M_Rock_Sandstone'"));
	if (MaterialEsc.Succeeded())
	{
		MallaDisparo->SetMaterial(0, MaterialEsc.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No se pudo cargar el material de disparo"));
	}
	
	// Inicializar la posición objetivo
	PosicionObjetivo = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void AFEscombro::BeginPlay()
{
	Super::BeginPlay();
	// Buscar al jugador
	Jugador = Cast<ABombBotCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// Si no se ha establecido una posición objetivo manualmente, capturar la posición actual del jugador
	if (PosicionObjetivo == FVector::ZeroVector)
	{
		ABombBotCharacter* Player = Cast<ABombBotCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player)
		{
			PosicionObjetivo = Player->GetActorLocation();
		}
	}

	// Activar física justo antes de atacar
	MallaDisparo->SetSimulatePhysics(true);

	// Usar un timer pequeño para dar tiempo a que se inicialice todo
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFEscombro::Atacar, 0.1f, false);
}

// Called every frame
void AFEscombro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Jugador)
	{
		float Distancia = FVector::Dist(GetActorLocation(), Jugador->GetActorLocation());

		if (Distancia <= RangoDeImpacto)
		{
			Jugador->TakeDamageAndLoseLife();
			UE_LOG(LogTemp, Warning, TEXT("Jugador dañado por proximidad"));
			Destroy(); // Destruye el disparo
		}
	}
}

void AFEscombro::SetPosicionObjetivo(const FVector& NuevaPosicionObjetivo)
{
	PosicionObjetivo = NuevaPosicionObjetivo;
}

void AFEscombro::Atacar()
{
	// Usar la posición objetivo fija en lugar de la posición actual del jugador
	if (PosicionObjetivo != FVector::ZeroVector)
	{
		FVector Direction = PosicionObjetivo - GetActorLocation();
		Direction.Normalize();

		// Asegurar que la física esté activada
		if (!MallaDisparo->IsSimulatingPhysics())
		{
			MallaDisparo->SetSimulatePhysics(true);
		}

		// Aplicar impulso más fuerte
		MallaDisparo->AddImpulse(Direction * VelocidadDisparo, NAME_None, true);

		UE_LOG(LogTemp, Log, TEXT("Disparo lanzado hacia posición objetivo: %s"), *PosicionObjetivo.ToString());
		UE_LOG(LogTemp, Log, TEXT("Dirección del disparo: %s"), *Direction.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No se ha establecido una posición objetivo válida"));
	}
}

void AFEscombro::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Verificar si el actor que colisionó es el jugador
	if (Other && Other->IsA(ABombBotCharacter::StaticClass()))
	{
		ABombBotCharacter* Player = Cast<ABombBotCharacter>(Other);
		if (Player)
		{
			Player->TakeDamageAndLoseLife(); // Llamar al método de reducir vida del jugador
			UE_LOG(LogTemp, Log, TEXT("Disparo impactó al jugador"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Disparo impactó con: %s"), Other ? *Other->GetName() : TEXT("Unknown"));
	}

	// Destruir el disparo en cualquier caso
	Destroy();
}

