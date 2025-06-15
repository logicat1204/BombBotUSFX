// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

UCLASS()
class BOMBBOT_API AExplosion : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExplosion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	APawn* PlayerForScore;
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ExplosionMesh;

	FVector InitialPosition;
	FVector NewPosition;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(EditDefaultsOnly, Category = "Efectos")
	UParticleSystem* ExplosionEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Efectos")
	FVector ExplosionScale = FVector(2.0f); // Puedes ajustar a 2.0, 3.0, etc.

public:

	float MoveSpeed = 3000.0f;
	float TraveledDistance = 0.0f;
	float TimeToDestroy = 2.0f;
	float TargetDistance = 500.0f;

	FVector MoveDirection = FVector(1, 0, 0);
	FVector CurrentPosition;
	FVector DeltaMove;

	void efecto_explosion(FVector Location);

	void AddScoreForExplosion(int32 Amount);
};
