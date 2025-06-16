// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#include "Power_Ups/PoweUp_Curacion.h"
#include "BombBotCharacter.h" 

APoweUp_Curacion::APoweUp_Curacion()
{
	PrimaryActorTick.bCanEverTick = false;
	MallaPowerUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPowerUp"));
	MallaPowerUp->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaP(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Blender/Power_UpCuracion_modelo.Power_UpCuracion_modelo'"));

	if (ObjetoMallaP.Succeeded())
	{
		MallaPowerUp->SetStaticMesh(ObjetoMallaP.Object);
		//MallaPowerUp->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	}
}

bool APoweUp_Curacion::ActivatePowerUp(ABombBotCharacter* PlayerCharacter)
{

	Super::ActivatePowerUp(PlayerCharacter);


	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PowerUp_Curacion: Intento de activacion sin un personaje valido."));
		return false;
	}

	PlayerCharacter->RecoverLives(CantidadCuracion);

	UE_LOG(LogTemp, Log, TEXT("PowerUp de curacion activado para %s. Vidas recuperadas: %d"), *PlayerCharacter->GetName(), CantidadCuracion);

	return true;
}
