// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Jefe1/JefeFinal.h"
#include "BombBot/Jefe1/HitboxJefe.h"
#include "BombBot/Jefe1/FSpawnerDisparos.h"
#include "BombBot/Jefe1/FSpawnerEscombros.h"
#include "BombBot/Jefe1/FSpawnerEsbirros.h"

// Sets default values
AJefeFinal::AJefeFinal()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshJefe = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MallaJefe"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EsqueletoJefe(TEXT("/Script/Engine.SkeletalMesh'/Game/AlvaroAssets/FinalBoss/tentacle-robot/source/Robot_export2.Robot_export2'"));
	if (EsqueletoJefe.Succeeded())
	{
		MeshJefe->SetSkeletalMesh(EsqueletoJefe.Object);
		MeshJefe->SetRelativeLocation(FVector(0.0f,0.0f,0.0f));
		MeshJefe->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	MeshJefe->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	MeshJefe->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialJefe(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/FinalBoss/tentacle-robot/textures/M_JefeFinal.M_JefeFinal'"));
	if (MaterialJefe.Succeeded())
	{
		MeshJefe->SetMaterial(0, MaterialJefe.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialJefe2(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/FinalBoss/tentacle-robot/textures/M_JefeFinal.M_JefeFinal'"));
	if (MaterialJefe2.Succeeded())
	{
		MeshJefe->SetMaterial(1, MaterialJefe2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimJefe(TEXT("/Script/Engine.AnimSequence'/Game/AlvaroAssets/FinalBoss/tentacle-robot/source/Robot_export2_Anim.Robot_export2_Anim'"));
	if (AnimJefe.Succeeded())
	{
		AnimJefeA = AnimJefe.Object;
	}

}

// Called when the game starts or when spawned
void AJefeFinal::BeginPlay()
{
	Super::BeginPlay();
	if (AnimJefeA)
	{
		MeshJefe->PlayAnimation(AnimJefeA, true);
	}
	SpawnHitBox();
	AsignSpawnerDisparos();
	AsignSpawnerEscombros();
	AssignSpawnerEsbirros();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AJefeFinal::DecidirAtaque, 10.0f, true); // Spawn the projectile spawner every 5 seconds
}

// Called every frame
void AJefeFinal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (VidaTotal == 10)
	{
		AttackNums = 5; // Increase the number of attacks when health reaches 10
		EscombrosAttacks = 4; // Increase the number of debris attacks when health reaches 10
		CantEsbirros = 2; // Increase the number of minions when health reaches 10
	}
	if (VidaTotal == 5)
	{
		AttackNums = 7; // Increase the number of attacks when health reaches 5
		EscombrosAttacks = 5; // Increase the number of debris attacks when health reaches 5
		CantEsbirros = 3; // Increase the number of minions when health reaches 5
	}
	if (VidaTotal == 0)
	{
		DeathEffect();
		if (SpawnerDisparos)
		{
			SpawnerDisparos->Destroy(); // Destroy the projectile spawner
			SpawnerDisparos = nullptr; // Clear the pointer to avoid dangling reference
		}
		if (SpawnerEscombros)
		{
			SpawnerEscombros->Destroy(); // Destroy the debris spawner
			SpawnerEscombros = nullptr; // Clear the pointer to avoid dangling reference
		}
		if (SpawnerEsbirros)
		{
			SpawnerEsbirros->Destroy(); // Destroy the minion spawner
			SpawnerEsbirros = nullptr; // Clear the pointer to avoid dangling reference
		}
		Destroy(); // Destroy the boss actor when health reaches 0
		return;
	}
}

// Called to bind functionality to input
void AJefeFinal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJefeFinal::SpawnHitBox()
{
	//Patron Singleton para evitar múltiples instancias de HitboxJefe
	if (HitboxJefe) return; // If HitboxJefe already exists, do not spawn a new one
	HitboxJefe = GetWorld()->SpawnActor<AHitboxJefe>(AHitboxJefe::StaticClass(), GetActorLocation()+FVector(0.0f,0.0f,-300.0f), GetActorRotation());
	if (HitboxJefe)
	{
		HitboxJefe->OnDestroyed.AddDynamic(this, &AJefeFinal::DestroyedHitbox);
	}
}

void AJefeFinal::DestroyedHitbox(AActor* DestroyedActor)
{
	if (VidaTotal > 0)
	{
		VidaTotal--; // Decrease the boss's health when the hitbox is destroyed
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Vida del Jefe: %d"), VidaTotal));
	}
	if (HitboxJefe)
	{
		HitboxJefe = nullptr; // Clear the pointer to avoid dangling reference
	}
	// Optionally, you can respawn the hitbox after a delay or based on some condition
	if (VidaTotal <= 0) return; // If the boss is defeated, do not respawn the hitbox
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AJefeFinal::SpawnHitBox, 5.0f, false); // Respawn after 5 seconds
}

void AJefeFinal::AsignSpawnerDisparos()
{
	SpawnerDisparos = GetWorld()->SpawnActor<AFSpawnerDisparos>(AFSpawnerDisparos::StaticClass(), GetActorLocation(), GetActorRotation());
	if (SpawnerDisparos)
	{
		SpawnerDisparos->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 100.0f)); // Adjust the spawn location if needed
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error al crear el Spawner de Disparos"));
	}
}

void AJefeFinal::SpawnSpawnerDisparos()
{
	if (SpawnerDisparos)
	{
		SpawnerDisparos->Atacar(AttackNums); // Call the attack method to spawn projectiles
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error al crear el Spawner de Disparos"));
	}
}

void AJefeFinal::AsignSpawnerEscombros()
{
	SpawnerEscombros = GetWorld()->SpawnActor<AFSpawnerEscombros>(AFSpawnerEscombros::StaticClass(), GetActorLocation(), GetActorRotation());
	if (SpawnerEscombros)
	{
		SpawnerEscombros->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 100.0f)); // Adjust the spawn location if needed
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error al crear el Spawner de Disparos"));
	}
}

void AJefeFinal::AttackEscombros()
{
	if (SpawnerEscombros)
	{
		SpawnerEscombros->AtacarES(EscombrosAttacks); // Call the attack method to spawn debris
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error al crear el Spawner de Escombros"));
	}
}

void AJefeFinal::AssignSpawnerEsbirros()
{
	SpawnerEsbirros = GetWorld()->SpawnActor<AFSpawnerEsbirros>(AFSpawnerEsbirros::StaticClass(), GetActorLocation(), GetActorRotation());
	if (SpawnerEsbirros)
	{
		SpawnerEsbirros->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 100.0f)); // Adjust the spawn location if needed
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error al crear el Spawner de Esbirros"));
	}
}

void AJefeFinal::SummonEsbirros()
{
	if (SpawnerEsbirros)
	{
		SpawnerEsbirros->SpawnEsbirros(CantEsbirros); // Spawn the minions
	}
}

void AJefeFinal::DecidirAtaque()
{
	Decision = FMath::RandRange(1, 3); // Randomly decide the type of attack
	if (Decision == 1)
	{
		SpawnSpawnerDisparos(); // Attack with projectiles
	}
	else if (Decision == 2)
	{
		AttackEscombros(); // Attack with debris
	}
	else if (Decision == 3)
	{
		SummonEsbirros(); // Summon minions
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Decisión de ataque inválida"));
	}
}

void AJefeFinal::DeathEffect()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("¡El Jefe ha sido derrotado!"));
}

