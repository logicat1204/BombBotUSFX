// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WUI_Principal.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBOT_API UWUI_Principal : public UUserWidget
{
	 GENERATED_BODY()

public:
    // Número máximo de vidas
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vida")
    int32 MaxVida = 3;

    // Número actual de vidas
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vida")
    int32 VidaActual;

    //Numero maximo de bombas
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bombas")
    int32 MaxBombas = 3;

    //Numero actual de bombas
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bombas")
    int32 BombasActuales;

    // Función para reducir vida
    UFUNCTION(BlueprintCallable, Category = "Vida")
    void ReducirVida();

    // Función para recuperar vida
    UFUNCTION(BlueprintCallable, Category = "Vida")
    void RecuperarVida();

    //Funcion para reducir bombas
    UFUNCTION(BlueprintCallable, Category = "Bombas")
    void ReducirBombas();

    //Funcion para restaurar bombas
    UFUNCTION(BlueprintCallable, Category = "Bombas")
    void AumentarBombas();

    //Funcion para updatear score.
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AumentarScore(int32 AddScore);

    //Funcion para updatear score.
    UFUNCTION(BlueprintCallable, Category = "Score")
    void ActualizarScore();

protected:
    virtual void NativeConstruct() override;

    // Punteros a las imágenes de baterias, enlazados desde Blueprint
    UPROPERTY(meta = (BindWidget))
    class UImage* Life1;

    UPROPERTY(meta = (BindWidget))
    UImage* Life2;

    UPROPERTY(meta = (BindWidget))
    UImage* Life3;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CantBombs;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ScoreTXT;

private:
    void ActualizarSalud();
    void ActualizarBombas();
};
