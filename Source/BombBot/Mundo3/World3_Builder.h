// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ILevels_Builder.h"
#include "GameFramework/Actor.h"
#include "World3_Builder.generated.h"

UCLASS()
class BOMBBOT_API AWorld3_Builder : public AActor, public IILevels_Builder
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorld3_Builder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//ASIGNAMOS EL FACTORY QUE SE VA A UTILIZAR PARA CREAR EL NIVEL
	class AWorld3_Factory* Factory;

	/// Implementación de la interfaz IILevelsBuilder
	virtual void BuildMap() override;
	virtual void BuildEnemy(int32 CantidadEnemigos) override;
	virtual void BuildPowerUps(int32 CantidadPowerUps) override;
	virtual void BuildPortals() override;
	virtual void SetStartPosition() override;
	virtual void FinalizeLevel() override;
};
