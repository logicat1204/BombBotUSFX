// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomba.generated.h"

class ALockSphere;

UCLASS()
class BOMBBOT_API ABomba : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABomba();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	USkeletalMeshComponent* MallaBomba;
	UAnimationAsset* AnimacionBomba;

	UPROPERTY(EditDefaultsOnly, Category = "Efectos")
	UParticleSystem* ExplosionEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Efectos")
	FVector ExplosionScale = FVector(2.0f); // Puedes ajustar a 2.0, 3.0, etc.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* SonidoBomba;
	USoundBase* SonidoColocar;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerHandle TimerHandle_Disparar;
	void Shoot();

	TArray<FVector> Direcciones;
	//segundos en los que explotara la bomba
	FTimerHandle TH_Explosion;
	float tiempo_explosion = 2.5f;


	void explotar();

	void explotar_en_cadena();
	bool NormalExp=false;

	void efecto_explosion(FVector Location);

public:
	APawn* Jugador;
	void SearchPlayerAndSetObstacle();

public:
	ALockSphere* WallBomba=nullptr;
	bool WallPlaced = false;
	UFUNCTION()
	void OnWallDestroyed(AActor* DestroyedActor);
};
