// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Enemigos/Enemigo.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Enemigo_Bomb.generated.h"
/**
 * 
 */
UCLASS()
class BOMBBOT_API AEnemigo_Bomb : public AEnemigo
{
	GENERATED_BODY()
	
public:

    AEnemigo_Bomb();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
public:
    //Metodos
 // Función para ir al siguiente punto
    void IrAlSiguientePunto();

    //Editar
    void ReanudarPatrulla();

    //Editar
    static void ReiniciarDeteccion(UWorld* World);


    //--------------------------------------EXPLOSION---------------------------------------------------
protected:

    UPROPERTY(EditAnywhere)
    float TiempoParaExplotar = 4.0f;

    UPROPERTY(EditAnywhere)
    float RangoExplosion = 3;

    FTimerHandle TimerHandle_Explosion;

    UFUNCTION()

    void ActivarExplosion();

    void Explotar();

    void ExplorarEnDireccion(FVector Direccion);

    UPROPERTY(EditAnywhere, Category = "FX")
    UNiagaraSystem* EfectoExplosion;

    bool bExplosionActivada = false;

    bool bJugadorDetectadoBomb = false;
};