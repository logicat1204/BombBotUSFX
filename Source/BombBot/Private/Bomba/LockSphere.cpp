// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomba/LockSphere.h"

// Sets default values
ALockSphere::ALockSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MallaEBloqueo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEBloqueo"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MallaEsfera(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MallaEsfera.Succeeded())
	{
		MallaEBloqueo->SetStaticMesh(MallaEsfera.Object);
		MallaEBloqueo->SetVisibility(false);
	}
}

// Called when the game starts or when spawned
void ALockSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALockSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

