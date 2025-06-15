// Fill out your copyright notice in the Description page of Project Settings.


#include "BombBot/Display/WUI_Principal.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWUI_Principal::NativeConstruct()
{
    Super::NativeConstruct();

    VidaActual = MaxVida;
    ActualizarSalud();
    BombasActuales = MaxBombas;
    ActualizarBombas();
}

void UWUI_Principal::ReducirVida()
{
    if (VidaActual > 0)
    {
        VidaActual--;
        ActualizarSalud();
    }
}

void UWUI_Principal::ReducirBombas()
{
    if (BombasActuales > 0)
    {
        BombasActuales--;
        ActualizarBombas();
    }
}

void UWUI_Principal::AumentarBombas()
{
    if (BombasActuales < 3)
    {
        BombasActuales++;
        ActualizarBombas();
    }
}

void UWUI_Principal::ActualizarSalud()
{
    // Oculta corazones según la vida actual
    if (Life1) Life1->SetVisibility(VidaActual >= 1 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    if (Life2) Life2->SetVisibility(VidaActual >= 2 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    if (Life3) Life3->SetVisibility(VidaActual >= 3 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UWUI_Principal::ActualizarBombas()
{
    if (CantBombs)
    {
        CantBombs->SetText(FText::AsNumber(BombasActuales));
    }
}
