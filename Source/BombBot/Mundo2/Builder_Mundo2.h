// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Builder_Mundo2.generated.h"

UCLASS()
class BOMBBOT_API ABuilder_Mundo2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilder_Mundo2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AWorld2_Builder* Builder;
	class ALevels_Director* Director;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
