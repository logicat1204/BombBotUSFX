// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Jefe1/FSpawnerEscombros.h"
#include "BombBotCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BombBot/Jefe1/FEscombro.h"

// Sets default values
AFSpawnerEscombros::AFSpawnerEscombros()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void AFSpawnerEscombros::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFSpawnerEscombros::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Player = Cast<ABombBotCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Spawner de Escombros activo"));
		FVector PlayerLocation = Player->GetActorLocation();
		SetActorLocation(FVector(PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z + 500.0f)); // Adjust Z to spawn above the player
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player not found!"));
	}
}

void AFSpawnerEscombros::AtacarES(int32 CantDisparos)
{
	for (int32 i = 0; i <= CantDisparos; i++)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFSpawnerEscombros::SpawnAtack, 1.0f * i, false);
	}
}

void AFSpawnerEscombros::SpawnAtack()
{
	// Spawn the projectile actor
	AFEscombro* Escombro = GetWorld()->SpawnActor<AFEscombro>(AFEscombro::StaticClass(), GetActorLocation(), GetActorRotation());
}

