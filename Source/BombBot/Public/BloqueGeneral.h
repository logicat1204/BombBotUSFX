// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BloqueGeneral.generated.h"
class ASubBloqueBase;
UCLASS()
class BOMBBOT_API ABloqueGeneral : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABloqueGeneral();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MallaBloque;	
	TArray<ASubBloqueBase*> SubBloquesGuardados;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 durabilidad=1;
	int32 estado=1; //Si es 1 vivo, si es 0 eliminado.
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	virtual void DestruirBloque();
	void ActivarDesvanecimientoSubbloques();
	void Impactar();
};
