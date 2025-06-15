// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BombBotCharacter.h"
#include "PowerUp.generated.h"
UCLASS()
class BOMBBOT_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APowerUp(); // <--- Corregido: PoweUp a PowerUp

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual bool ActivatePowerUp(ABombBotCharacter* PlayerCharacter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components") // <--- Corregido: VisibleAnyWhere a VisibleAnywhere
		class UBoxComponent* PowerUpCollision;             // <--- Corregido: UboxComponent a UBoxComponent (B may�scula)

	UPROPERTY(VisibleAnywhere, Category = "Components") // <--- Corregido: VisibleAnyWhere a VisibleAnywhere
		class UStaticMeshComponent* PowerUpMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components") // <--- Corregido: VisibleAnyWhere a VisibleAnywhere
		class URotatingMovementComponent* RotatingMovement;

	// Adelantamos la declaraci�n de ABombBotCharacter para evitar inclusi�n circular
	// o dependencias innecesarias en el .h. La inclusi�n completa (#include "BombBotCharacter.h")
	// se har�a en el archivo .cpp si fuera necesario.

public:
	virtual void Tick(float DeltaTime) override;
};