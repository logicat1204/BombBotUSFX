// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "FDisparo.generated.h"

UCLASS()
class BOMBBOT_API AFDisparo : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFDisparo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MallaDisparo;

	// Posición objetivo fija capturada al momento de la instanciación
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	FVector PosicionObjetivo;

	// Velocidad del proyectil
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float VelocidadDisparo = 1000.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Función para establecer la posición objetivo
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetPosicionObjetivo(const FVector& NuevaPosicionObjetivo);

	// Función de ataque
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Atacar();

	// Función de colisión
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};