// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomba/Bomba.h"
#include "Bomba/Explosion.h"
//Para efecto explosion
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

//incluir bloque que tapa a este bloque
#include "Bomba/LockSphere.h"

// Sets default values
ABomba::ABomba()
{
    PrimaryActorTick.bCanEverTick = true;

    MallaBomba = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MallaBomba"));
    RootComponent = MallaBomba; // Importante que la malla sea root, o SetupAttachment

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> ObjetoMallaBomba(TEXT("/Script/Engine.SkeletalMesh'/Game/ActionsCharacter/Bomb/SKM_Robot.SKM_Robot'"));
    if (ObjetoMallaBomba.Succeeded()) {
        MallaBomba->SetSkeletalMesh(ObjetoMallaBomba.Object);
        MallaBomba->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        MallaBomba->SetRelativeScale3D(FVector(0.9f, 0.9f, 0.9f));
    }

    static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimacionAsset(TEXT("/Game/ActionsCharacter/Bomb/SKM_Robot_Anim"));
    if (AnimacionAsset.Succeeded()) {
        AnimacionBomba = AnimacionAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionEffectAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
    if (ExplosionEffectAsset.Succeeded())
    {
        ExplosionEffect = ExplosionEffectAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Sounds/Bomb/explosion1.explosion1"));

    if (SoundAsset.Succeeded())
    {
        SonidoBomba = SoundAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset2(TEXT("/Script/Engine.SoundWave'/Game/Sounds/Bomb/place_bomb1.place_bomb1'"));
    if (SoundAsset2.Succeeded())
    {
        SonidoColocar = SoundAsset2.Object;
    }
}

// Called when the game starts or when spawned
void ABomba::BeginPlay()
{
    Super::BeginPlay();

    //Obtener al jugador
    Jugador = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    //Reproducir sonido al colocar la bomba
    UGameplayStatics::PlaySoundAtLocation(this, SonidoColocar, GetActorLocation());
    if (AnimacionBomba)
    {
        MallaBomba->PlayAnimation(AnimacionBomba, true);
        GEngine->AddOnScreenDebugMessage(1, 15.0f, FColor::Black, TEXT("Se ha reproducido la animacion de la bomba"));
    }
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_Disparar, this, &ABomba::Shoot, tiempo_explosion, false); // Dispara cada 5 segundos
    GetWorld()->GetTimerManager().SetTimer(TH_Explosion, this, &ABomba::explotar, tiempo_explosion + 0.05f, false);
}

// Called every frame
void ABomba::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    SearchPlayerAndSetObstacle();
}


void ABomba::Shoot()
{
    Direcciones = {
        FVector(1, 0, 0),
        FVector(-1, 0, 0),
        FVector(0, 1, 0),
        FVector(0, -1, 0)
    };

    for (const FVector& Dir : Direcciones)
    {
        FRotator Rotacion = Dir.Rotation(); // Obtener la rotación que mira en esa dirección
        AExplosion* NuevaExplosion = GetWorld()->SpawnActor<AExplosion>(GetActorLocation(), Rotacion);
        if (NuevaExplosion)
        {
            NuevaExplosion->MoveDirection = Dir;
        }
    }
}

void ABomba::explotar()
{
    if (WallBomba)
    {
        NormalExp = true;
        WallBomba->Destroy();
    }
    Destroy();
    FVector ubi_explosion = GetActorLocation();
    efecto_explosion(ubi_explosion);
    //Reproducir el sonido
    UGameplayStatics::PlaySoundAtLocation(this, SonidoBomba, GetActorLocation());
}

void ABomba::efecto_explosion(FVector Location)
{
    if (ExplosionEffect && GetWorld())
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            ExplosionEffect,
            Location,
            FRotator::ZeroRotator,
            ExplosionScale,  // Aquí se aplica la escala
            true
        );
    }
}

void ABomba::SearchPlayerAndSetObstacle()
{
    if (WallPlaced == false)
    {
        if (Jugador)
        {
            FVector player_pos = Jugador->GetActorLocation();
            float dist = FVector::Dist(player_pos, GetActorLocation());
            if (dist < 200.0f)
            {
                return;
            }
            else if (dist > 200.0f)
            {
                WallPlaced = true;
                WallBomba = GetWorld()->SpawnActor<ALockSphere>(ALockSphere::StaticClass(), GetActorLocation(), FRotator::ZeroRotator);
                if (WallBomba) 
                {
                    WallBomba->OnDestroyed.AddDynamic(this, &ABomba::OnWallDestroyed);
                }
            }
        }
    }
}

void ABomba::OnWallDestroyed(AActor* DestroyedActor)
{
   /* FTimerHandle ChainReactionTime;
    GetWorldTimerManager().SetTimer(ChainReactionTime, this, &ABomba::explotar_en_cadena, 0.1f, false);*/
    explotar_en_cadena();
}

void ABomba::explotar_en_cadena()
{
    if (WallBomba)
    {
        WallBomba->Destroy();
    }
    if (NormalExp == false)
    {
        Shoot();
        explotar();
    }
}
