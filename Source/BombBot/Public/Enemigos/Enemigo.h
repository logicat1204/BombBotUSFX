// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "Enemigo.generated.h"

UCLASS()
class BOMBBOT_API AEnemigo : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemigo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    //Atributos

    // Malla estática del cubo
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Malla;

    // Propiedad para asignar el Animation Blueprint desde el editor de Unreal
        UPROPERTY(EditDefaultsOnly, Category = "Animation")
        TSubclassOf<UAnimInstance> AnimationBlueprint;
    
    // Referencia al jugador
    AActor* PlayerActor;

    // Controlador de IA
    AAIController* AIController;

    // Patrullaje
    UPROPERTY(EditAnywhere, Category = "Patrullaje")
    TArray<ATargetPoint*> PuntosDePatrulla;

    int32 IndicePatrullaActual = 0;

    FTimerHandle TimerEspera;

    UPROPERTY(EditAnywhere, Category = "Patrullaje")
    float TiempoEspera = 2.0f;

    bool bEsperando = false;

    //Nuevo
public:
    //Atributos
    static bool bJugadorDetectado;
    static FTimerHandle TimerReiniciarDeteccion;


    // Tiempo sin ver al jugador antes de reiniciar detección
    static constexpr float TiempoParaReiniciar = 5.0f;
};
