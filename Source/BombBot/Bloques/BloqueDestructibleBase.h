// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BloqueDestructibleBase.generated.h"
class ASubBloqueBase;
UCLASS()
class BOMBBOT_API ABloqueDestructibleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABloqueDestructibleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;
	TArray<ASubBloqueBase*> SubBloquesGuardados;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void DestruirBloque();
	void ActivarDesvanecimientoSubbloques();

};
