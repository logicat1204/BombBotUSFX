// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Jefe1/HitboxJefe.h"

// Sets default values
AHitboxJefe::AHitboxJefe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitboxJefeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitboxJefeMesh"));
	RootComponent = HitboxJefeMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HitboxMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Tube.Shape_Tube'"));
	if (HitboxMeshAsset.Succeeded())
	{
		HitboxJefeMesh->SetStaticMesh(HitboxMeshAsset.Object);
		HitboxJefeMesh->SetVisibility(false);
	}
	HitboxJefeMesh->SetRelativeScale3D(FVector(1.f, 1.f, 2.5f));
}

// Called when the game starts or when spawned
void AHitboxJefe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitboxJefe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

