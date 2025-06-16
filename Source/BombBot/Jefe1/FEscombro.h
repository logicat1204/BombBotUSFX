// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FEscombro.generated.h"

class ABombBotCharacter;
UCLASS()
class BOMBBOT_API AFEscombro : public AActor
{
	GENERATED_BODY()
public:
	AFEscombro();
	float RangoDeImpacto = 100.0f;
	ABombBotCharacter* Jugador;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MallaDisparo;

	// Posici�n objetivo fija capturada al momento de la instanciaci�n
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	FVector PosicionObjetivo;

	// Velocidad del proyectil
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float VelocidadDisparo = 1000.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Funci�n para establecer la posici�n objetivo
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetPosicionObjetivo(const FVector& NuevaPosicionObjetivo);

	// Funci�n de ataque
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Atacar();

	// Funci�n de colisi�n
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
