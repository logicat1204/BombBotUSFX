// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Comun.h"
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
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "BombBotCharacter.h"
#include "PowerUps_Factory.h"
#include "Components/CapsuleComponent.h"

AEnemigo_Comun::AEnemigo_Comun()
{
    PrimaryActorTick.bCanEverTick = true;
    
    // Configuración de la caja de colisión de ataque
       AttackCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionBox"));
       // Adjuntar al CapsuleComponent principal o al RootComponent
       AttackCollisionBox->SetupAttachment(GetCapsuleComponent()); // Adjuntar a la cápsula principal
       // O: AttackCollisionBox->SetupAttachment(RootComponent); // Si quieres que esté en la raíz

       // Ajusta la posición, rotación y tamaño de la caja según necesites
       // Esto es relativo al componente al que está adjunto (GetCapsuleComponent() aquí)
       AttackCollisionBox->SetRelativeLocation(FVector(60.0f, 0.0f, 0.0f)); // Ejemplo: 60 unidades delante del centro de la cápsula
       AttackCollisionBox->SetBoxExtent(FVector(30.0f, 30.0f, 30.0f)); // Ejemplo: tamaño de la caja (medio lado)

       // Configurar la colisión de la caja
       AttackCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Solo consultas (para Overlap), no bloquea físicas
       AttackCollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1); // Puedes usar un canal personalizado si lo has definido
       AttackCollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); // Ignorar todo por defecto
       AttackCollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap); // SUPERPONERSE con el jugador (canal Pawn)

       // Asegúrate de que la caja pueda generar eventos de superposición
       AttackCollisionBox->SetGenerateOverlapEvents(true);

    // NO cargar el Skeletal Mesh aquí. Permitir que se asigne en el Blueprint.
    // Solo se realiza la configuración básica si es necesario.
    USkeletalMeshComponent* CharacterMesh = GetMesh();

    if (CharacterMesh)
    {
        // Ajustar la posición, rotación y escala del mesh si es necesario
        // Estos valores son en relación al componente padre (CapsuleComponent en este caso)
        CharacterMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
        CharacterMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
        CharacterMesh->SetRelativeScale3D(FVector(1.0f));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterMesh (GetMesh()) is null in AEnemigoAcuatico constructor!"));
    }
    
    // IA
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AAIController::StaticClass();

    // Velocidad de movimiento
    GetCharacterMovement()->MaxWalkSpeed = 200.0f;

    // Asegúrate de que tu CapsuleComponent esté configurado para generar eventos de hit
    // Esto se puede hacer en el editor o en C++:
    GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
}

void AEnemigo_Comun::BeginPlay()
{
    Super::BeginPlay();
    
    // Vincular el evento de superposición para la caja de ataque
       if (AttackCollisionBox)
       {
           AttackCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemigo_Comun::OnAttackBoxOverlap);
       }
       else
       {
           UE_LOG(LogTemp, Error, TEXT("AttackCollisionBox es nulo en BeginPlay de AEnemigo_Comun!"));
       }

    AIController = Cast<AAIController>(GetController());
    if (!AIController)
    {
        UE_LOG(LogTemp, Warning, TEXT("No se pudo obtener el AIController"));
    }

    // Configurar el evento de colision
    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemigo_Comun::OnHitJugador);

    // Patrulla hasta el siguiente punto
    if (PuntosDePatrulla.Num() > 0)
    {
        IrAlSiguientePunto();
    }

    // Obtener el jugador
    PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemigo_Comun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //Dibujar la capsula del enemigo
    DrawDebugCapsule(GetWorld(), GetCapsuleComponent()->GetComponentLocation(),
                     GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
                     GetCapsuleComponent()->GetScaledCapsuleRadius(),
                     GetCapsuleComponent()->GetComponentQuat(),
                     FColor::Green, false, 0.1f, 0, 2.0f);
    
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    if (CharacterMesh)
    {
        // Asignar el Animation Blueprint si ha sido establecido en el editor
        if (AnimationBlueprint)
        {
            CharacterMesh->SetAnimInstanceClass(AnimationBlueprint);
            UE_LOG(LogTemp, Log, TEXT("Animation Blueprint assigned to mesh in BeginPlay!"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("AnimationBlueprint is not set for AEnemigoAcuatico!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterMesh (GetMesh()) is null in AEnemigoAcuatico::BeginPlay()!"));
    }
    
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
    
    // Si cualquier enemigo vio al jugador, o este lo est· viendo
    if (bJugadorDetectado || (Distancia <= RangoVision && Angulo <= AnguloVision))
    {
        bJugadorDetectado = true;  // Si este enemigo lo ve, notifica a los dem·s
        
        //GetCharacterMovement()->MaxWalkSpeed = 400.0f;
        AIController->MoveToActor(PlayerActor, 0.0f);
        if (IsValid(this) && !IsActorBeingDestroyed() && GetWorld())
        {
            GetWorldTimerManager().ClearTimer(TimerEspera);
            bEsperando = false;
        }
        bEsperando = false;
    }
    else if (!bEsperando && AIController->GetMoveStatus() == EPathFollowingStatus::Idle && PuntosDePatrulla.Num() > 0)
    {
        bEsperando = true;
        GetWorldTimerManager().SetTimer(TimerEspera, this, &AEnemigo_Comun::IrAlSiguientePunto, TiempoEspera, false);
    }
}

void AEnemigo_Comun::KillEnemigo()
{
    ProbabilidadSpawnPowerUp = FMath::RandRange(0.0f, 1.0f);

    if (ProbabilidadSpawnPowerUp < 0.5f) // 20% de probabilidad
    {
        APowerUps_Factory* PowerUpFactory = GetWorld()->SpawnActor<APowerUps_Factory>(APowerUps_Factory::StaticClass());

        if (PowerUpFactory)
        {
            int PowerUpIndex = FMath::RandRange(1, 3);
            PowerUpFactory->CreatePowerUp(GetActorLocation(), PowerUpIndex);
            PowerUpFactory->Destroy(); 
        }
    }

    Destroy();  // Destruye el enemigo
}


void AEnemigo_Comun::IrAlSiguientePunto()
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

void AEnemigo_Comun::OnHitJugador(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor == PlayerActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("El enemigo toco al jugador!"));

        // Intentar castear el OtherActor a tu clase de personaje
        ABombBotCharacter* PlayerCharacter = Cast<ABombBotCharacter>(OtherActor);

        if (PlayerCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemigo toco a: %s"), *PlayerCharacter->GetName());
            // Llamar a la funciÛn para que el jugador pierda una vida
            PlayerCharacter->TakeDamageAndLoseLife();

            // AquÌ podrÌas anadir logica adicional para el enemigo, como:
            // - Destruirse a si mismo despuÈs de daÒar al jugador: Destroy();
            // - Desactivar su colisiÛn por un tiempo para no daÒar repetidamente:
            //   CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            //   FTimerHandle TempTimer;
            //   GetWorldTimerManager().SetTimer(TempTimer, [this]() { if(CollisionComp) CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly); }, 2.0f, false);
        }
    }
}

void AEnemigo_Comun::OnAttackBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    // Asegúrate de que el actor superpuesto sea el jugador y no sea el propio enemigo
    if (OtherActor && OtherActor == PlayerActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Caja de ataque del enemigo hizo OVERLAP con el jugador"));

        ABombBotCharacter* PlayerCharacter = Cast<ABombBotCharacter>(OtherActor);

        if (PlayerCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemigo dano a: %s"), *PlayerCharacter->GetName());
            PlayerCharacter->TakeDamageAndLoseLife();

            // Opcional: Desactivar la caja de ataque temporalmente para evitar daño múltiple instantáneo
            AttackCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            FTimerHandle TempTimer;
            GetWorldTimerManager().SetTimer(TempTimer, [this]() {
                if (IsValid(this) && AttackCollisionBox)
                {
                    AttackCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
                }
            }, 1.0f, false); // Re-habilitar la caja de ataque después de 1 segundo
        }
    }
}
