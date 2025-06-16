// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Jefe1/JefeFinal.h"
#include "BombBot/Jefe1/HitboxJefe.h"

// Sets default values
AJefeFinal::AJefeFinal()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshJefe = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MallaJefe"));
	MeshJefe->SetupAttachment(RootComponent);
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
}

// Called every frame
void AJefeFinal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	HitboxJefe = GetWorld()->SpawnActor<AHitboxJefe>(AHitboxJefe::StaticClass(), GetActorLocation(), GetActorRotation());
	if (HitboxJefe)
	{
		HitboxJefe->OnDestroyed.AddDynamic(this, &AJefeFinal::DestroyedHitbox);
	}
}

void AJefeFinal::DestroyedHitbox()
{
	if (VidaTotal > 0)
	{
		VidaTotal--; // Decrease the boss's health when the hitbox is destroyed
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Vida del Jefe: %d"), VidaTotal));
	}
	if (HitboxJefe)
	{
		HitboxJefe->Destroy();
		HitboxJefe = nullptr; // Clear the pointer to avoid dangling reference
	}
	// Optionally, you can respawn the hitbox after a delay or based on some condition
	if (VidaTotal <= 0) return; // If the boss is defeated, do not respawn the hitbox
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AJefeFinal::SpawnHitBox, 5.0f, false); // Respawn after 5 seconds
}

