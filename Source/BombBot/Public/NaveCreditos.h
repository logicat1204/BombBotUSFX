// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BombBotCharacter.h"
#include "NaveCreditos.generated.h"
UCLASS()
class BOMBBOT_API ANaveCreditos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANaveCreditos();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, Category = "Nivel")
	TArray<FName> ListaNiveles;
protected:


	UPROPERTY(VisibleAnywhere, Category = "Components") // <--- Corregido: VisibleAnyWhere a VisibleAnywhere
		class UBoxComponent* PowerUpCollision;             // <--- Corregido: UboxComponent a UBoxComponent (B mayúscula)

	UPROPERTY(VisibleAnywhere, Category = "Components") // <--- Corregido: VisibleAnyWhere a VisibleAnywhere
		class UStaticMeshComponent* PowerUpMesh;

};
