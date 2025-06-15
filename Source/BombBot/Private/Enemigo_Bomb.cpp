// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemigo_Bomb.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include "Engine/TargetPoint.h"
#include "Navigation/PathFollowingComponent.h"
#include "DrawDebugHelpers.h"

AEnemigo_Bomb::AEnemigo_Bomb()
{
    PrimaryActorTick.bCanEverTick = true;

    // Crear el componente raíz
    GetMesh()->SetHiddenInGame(true);

    // Crear la malla estática
    Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
    Malla->SetupAttachment(RootComponent);

    // Configurar la malla estática
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CuboMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    if (CuboMesh.Succeeded())
    {
        // Asignar la malla estática
        Malla->SetStaticMesh(CuboMesh.Object);
        // Configurar la escala y la ubicación
        Malla->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
        // Configurar la escala
        Malla->SetWorldScale3D(FVector(1.0f));
        // Configurar la colisión
        //Para que el enemigo colisione con el jugador
        Malla->SetCollisionObjectType(ECC_Pawn);
        // Para que no colisione con lo demas
        Malla->SetCollisionResponseToAllChannels(ECR_Ignore);
        Malla->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
        Malla->SetGenerateOverlapEvents(true);
    }

    // IA
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AAIController::StaticClass();

    // Velocidad de movimiento
    GetCharacterMovement()->MaxWalkSpeed = 200.0f;

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EfectoNiagaraAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/Niagara_System/NS_Explosion.NS_Explosion'"));
    if (EfectoNiagaraAsset.Succeeded())
    {
        EfectoExplosion = EfectoNiagaraAsset.Object;
    }
}

void AEnemigo_Bomb::BeginPlay()
{
    Super::BeginPlay();

    AIController = Cast<AAIController>(GetController());
    if (!AIController)
    {
        UE_LOG(LogTemp, Warning, TEXT("No se pudo obtener el AIController"));
    }

    // Patrulla hasta el siguiente punto
    if (PuntosDePatrulla.Num() > 0)
    {
        IrAlSiguientePunto();
    }
    // Obtener el jugador
    PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
}

void AEnemigo_Bomb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerActor || !AIController) return;

    FVector DireccionAlJugador = (PlayerActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    FVector DireccionFrente = GetActorForwardVector();
    float Distancia = FVector::Dist(GetActorLocation(), PlayerActor->GetActorLocation());
    float Angulo = FMath::RadiansToDegrees(acosf(FVector::DotProduct(DireccionFrente, DireccionAlJugador)));

    const float RangoVision = 400.0f;
    const float AnguloVision = 30.0f;

    DrawDebugCone(GetWorld(), GetActorLocation(), DireccionFrente, RangoVision,
        FMath::DegreesToRadians(AnguloVision), FMath::DegreesToRadians(AnguloVision),
        12, FColor::Yellow, false, -1.0f, 0, 1.0f);

    bool bLoVeo = (Distancia <= RangoVision && Angulo <= AnguloVision);

    if (bLoVeo)
    {
        if (!bJugadorDetectadoBomb)
        {
            UE_LOG(LogTemp, Warning, TEXT("Jugador detectado por: %s"), *GetName());
        }

        bJugadorDetectadoBomb = true;
    }

    if (bJugadorDetectadoBomb)
    {
        GetCharacterMovement()->MaxWalkSpeed = 350.0f;

        // MOVER AL JUGADOR
        AIController->MoveToActor(PlayerActor, 15.0f);

        // Activar explosión solo una vez
        if (!bExplosionActivada)
        {
            ActivarExplosion();
            bExplosionActivada = true;
        }

        GetWorldTimerManager().ClearTimer(TimerEspera);
        bEsperando = false;

    }
    else if (!bEsperando && AIController->GetMoveStatus() == EPathFollowingStatus::Idle && PuntosDePatrulla.Num() > 0)
    {
        bEsperando = true;
        GetWorldTimerManager().SetTimer(TimerEspera, this, &AEnemigo_Bomb::IrAlSiguientePunto, TiempoEspera, false);
    }
    else if (!bJugadorDetectadoBomb)
    {
        // Volver a patrullar si no está esperando
        if (!bEsperando && PuntosDePatrulla.Num() > 0)
        {
            bEsperando = true;
            GetWorldTimerManager().SetTimer(TimerEspera, this, &AEnemigo_Bomb::ReanudarPatrulla, TiempoEspera, false);



            UE_LOG(LogTemp, Warning, TEXT("Enemigo %s vuelve a patrullar."), *GetName());
        }
    }
}

void AEnemigo_Bomb::IrAlSiguientePunto()
{
    if (PuntosDePatrulla.Num() == 0 || !AIController) return;

    ATargetPoint* PuntoActual = PuntosDePatrulla[IndicePatrullaActual];
    if (PuntoActual)
    {
        FAIMoveRequest MoveRequest;
        MoveRequest.SetGoalActor(PuntoActual);
        MoveRequest.SetAcceptanceRadius(5.0f);

        FPathFollowingRequestResult Resultado = AIController->MoveTo(MoveRequest);

        if (Resultado.Code != EPathFollowingRequestResult::Failed)
        {
            IndicePatrullaActual = (IndicePatrullaActual + 1) % PuntosDePatrulla.Num();
            bEsperando = false;
        }
    }
}

void AEnemigo_Bomb::ActivarExplosion()
{
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_Explosion, this, &AEnemigo_Bomb::Explotar, TiempoParaExplotar, false);
}

void AEnemigo_Bomb::Explotar()
{
    if (EfectoExplosion)
    {
        // Efecto de explosión en el centro de la bomba
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            EfectoExplosion,
            GetActorLocation(),
            FRotator::ZeroRotator
        );
    }

    ExplorarEnDireccion(FVector(1, 0, 0));   // Derecha
    ExplorarEnDireccion(FVector(-1, 0, 0));  // Izquierda
    ExplorarEnDireccion(FVector(0, 1, 0));   // Adelante
    ExplorarEnDireccion(FVector(0, -1, 0));  // Atrás

    Destroy(); // Destruir la bomba
}

void AEnemigo_Bomb::ExplorarEnDireccion(FVector Direccion)
{
    FVector Posicion = GetActorLocation();

    for (int i = 1; i <= RangoExplosion; ++i)
    {
        FVector CheckPos = Posicion + Direccion * i * 100.0f; // Tamaño de celda

        //Spawnea efecto visual en esa posición
        if (EfectoExplosion)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                EfectoExplosion,
                CheckPos,
                FRotator::ZeroRotator
            );
        }

        FHitResult Hit;
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);

        //if (GetWorld()->LineTraceSingleByChannel(Hit, Posicion, CheckPos, ECC_Visibility, Params))
        //{
        //    ABloqueBase* Bloque = Cast<ABloqueBase>(Hit.GetActor());
        //    if (Bloque)
        //    {
        //        if (Bloque->bEsDestructible)
         //       {
         //           Bloque->Destroy();
         //       }
             //   break; // Rompible o no, se detiene la explosión
           // }
            //else
           // {
           //     break; // Cualquier otro obstáculo también bloquea
            //}
        //}
    }
}

void AEnemigo_Bomb::ReanudarPatrulla()
{
    {
        if (PuntosDePatrulla.Num() > 0 && AIController)
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemigo %s reanuda patrulla."), *GetName());
            IrAlSiguientePunto();
        }
    }
}
