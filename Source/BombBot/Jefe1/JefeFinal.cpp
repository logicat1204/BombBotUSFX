// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Jefe1/JefeFinal.h"

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
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialJefe(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/FinalBoss/tentacle-robot/textures/Material_011_BaseColor_Mat.Material_011_BaseColor_Mat'"));
	if (MaterialJefe.Succeeded())
	{
		MeshJefe->SetMaterial(0, MaterialJefe.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialJefe2(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/FinalBoss/tentacle-robot/textures/Material_011_BaseColor_Mat.Material_011_BaseColor_Mat'"));
	if (MaterialJefe2.Succeeded())
	{
		MeshJefe->SetMaterial(1, MaterialJefe2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimJefe(TEXT("/Script/Engine.AnimSequence'/Game/AlvaroAssets/FinalBoss/tentacle-robot/source/Robot_export2_Anim.Robot_export2_Anim'"));
	if (AnimJefe.Succeeded())
	{
		MeshJefe->PlayAnimation(AnimJefe.Object, true);
	}
}

// Called when the game starts or when spawned
void AJefeFinal::BeginPlay()
{
	Super::BeginPlay();
	
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

