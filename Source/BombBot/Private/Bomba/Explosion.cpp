// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomba/Explosion.h"
#include "BloqueGeneral.h"
#include "BombBot/Bloques/Bloque_Madera.h"
#include "BombBot/Bloques/Bloque_Pasto.h"
#include "BombBot/Bloques/Bloque_Piedra.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "BombBotCharacter.h"
<<<<<<< HEAD
#include "Enemigo_Comun.h"
=======

//Para encender las otras bombas al impactarlas
#include "Bomba/Bomba.h"
#include "Bomba/LockSphere.h"

#include "Enemigo_Comun.h"

>>>>>>> RamaAlvaro
//Para efecto explosion
//kismet GameplayStatics tambien se usa
#include "Particles/ParticleSystem.h"


// Sets default values
AExplosion::AExplosion()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    ExplosionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExplosionMesh"));
    RootComponent = ExplosionMesh;

    ConstructorHelpers::FObjectFinder<UStaticMesh> ExplosionMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    //ConstructorHelpers::FObjectFinder<UStaticMesh> ExplosionMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/ActionsCharacter/LowPoly_Fireball/Sphere.Sphere'"));
    if (ExplosionMeshAsset.Succeeded())
    {
        ExplosionMesh->SetStaticMesh(ExplosionMeshAsset.Object);
        ExplosionMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
    }

    ConstructorHelpers::FObjectFinder<UMaterial> MaterialExplosionAsset(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));
    //ConstructorHelpers::FObjectFinder<UMaterial> MaterialExplosionAsset(TEXT("/Script/Engine.Material'/Game/ActionsCharacter/LowPoly_Fireball/Material_001.Material_001'"));
    if (MaterialExplosionAsset.Succeeded())
    {
        ExplosionMesh->SetMaterial(0, MaterialExplosionAsset.Object);
    }
    //aqui se carga el asset de la explosion para invocarlo con el tick a cada instante que se dibuja la explosion
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionEffectAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
    if (ExplosionEffectAsset.Succeeded())
    {
        ExplosionEffect = ExplosionEffectAsset.Object;
    }

    ExplosionMesh->SetSimulatePhysics(true);
    ExplosionMesh->SetNotifyRigidBodyCollision(true);
    ExplosionMesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
    ExplosionMesh->SetEnableGravity(false);
    ExplosionMesh->SetVisibility(false);

    ExplosionMesh->OnComponentHit.AddDynamic(this, &AExplosion::OnHit);
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
    Super::BeginPlay();

    InitialPosition = GetActorLocation();
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurrentPosition = GetActorLocation();
    DeltaMove = MoveDirection.GetSafeNormal() * MoveSpeed * DeltaTime;
    NewPosition = CurrentPosition + DeltaMove;
    SetActorLocation(NewPosition);

    efecto_explosion(NewPosition);

    TraveledDistance = FVector::Dist(InitialPosition, NewPosition);

    if (TraveledDistance >= TargetDistance)
    {
        Destroy();
    }
}

void AExplosion::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        if (OtherActor->IsA(ABloqueGeneral::StaticClass()))
        {
            if (ABloque_Pasto* BloqueP = Cast<ABloque_Pasto>(OtherActor))
            {
                BloqueP->Impactar();
                Destroy();
            }
            else if (ABloque_Madera* BloqueM = Cast<ABloque_Madera>(OtherActor)) {
                BloqueM->Impactar();
                Destroy();
            }
            else if (ABloque_Piedra* BloqueIN = Cast<ABloque_Piedra>(OtherActor)) {
                Destroy();
            }
        }
        else if (ACharacter* Jugador = Cast<ACharacter>(OtherActor))
        {
            // Intentar castear el OtherActor a tu clase de personaje
            ABombBotCharacter* PlayerCharacter = Cast<ABombBotCharacter>(OtherActor);

            if (PlayerCharacter)
            {
                UE_LOG(LogTemp, Warning, TEXT("Enemigo toco a: %s"), *PlayerCharacter->GetName());
                // Llamar a la función para que el jugador pierda una vida
                PlayerCharacter->TakeDamageAndLoseLife();

                // Aquí podrías añadir lógica adicional para el enemigo, como:
                // - Destruirse a sí mismo después de dañar al jugador: Destroy();
                // - Desactivar su colisión por un tiempo para no dañar repetidamente:
                //   CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                //   FTimerHandle TempTimer;
                //   GetWorldTimerManager().SetTimer(TempTimer, [this]() { if(CollisionComp) CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly); }, 2.0f, false);
            }
        }
<<<<<<< HEAD

        if (AEnemigo_Comun* Enemigo = Cast<AEnemigo_Comun>(OtherActor)) {

            Enemigo->Destroy();
        }

        //else if (OtherActor->IsA(AShield::StaticClass()))
        //{
        //    // Ejemplo: destruir el escudo al contacto
        //    OtherActor->Destroy();

        //    // Tal vez también destruir la explosión
        //    Destroy();
        //}
        //else if (AEnemigo* Enemigo = Cast<AEnemigo>(OtherActor))
        //{
        //    Enemigo->ReducirVida();
        //    Destroy();
        //}

=======
        if (AEnemigo_Comun* Enemigo = Cast<AEnemigo_Comun>(OtherActor))
        {
            Enemigo->Destroy();
            //Destroy();
        }
        if (ALockSphere* OtraBomba = Cast<ALockSphere>(OtherActor))
        {
            OtraBomba->Destroy();
            Destroy();
        }
>>>>>>> RamaAlvaro
    }
}

void AExplosion::efecto_explosion(FVector Location)
{
    if (ExplosionEffect && GetWorld())
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            ExplosionEffect,
            Location,
            FRotator::ZeroRotator,
            //ExplosionScale,  // Aquí se aplica la escala
            true
        );
    }
}
