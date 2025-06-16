// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque_Salida.h"

// Sets default values
ABloque_Salida::ABloque_Salida()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Añadimos una malla estática al actor
	MallaBloque = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBloque"));
	MallaBloque->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaBloque(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (ObjetoMallaBloque.Succeeded())
	{
		MallaBloque->SetStaticMesh(ObjetoMallaBloque.Object);
		MallaBloque->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	}
	if (MallaBloque)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/AlvaroAssets/NewBoxAsset/Textures/U_BOX2.U_BOX2'"));

		if (MaterialBase.Succeeded())
		{
			MallaBloque->SetMaterial(0, MaterialBase.Object);
		}
	}
}

// Called when the game starts or when spawned
void ABloque_Salida::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABloque_Salida::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

