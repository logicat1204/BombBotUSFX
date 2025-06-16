// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Power_Ups/PowerUp.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Persona.generated.h"

/**
 * 
 */
UCLASS()
class BOMBBOT_API APersona : public APowerUp
{
	GENERATED_BODY()

public:

	APersona();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* MiSkeletalMesh;
    
    // Usamos TSoftObjectPtr para las referencias a assets que se cargarán en tiempo de ejecución.
    // Esto permite que Blueprint también las asigne.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
    TSoftObjectPtr<USkeletalMesh> FoxSkeletalMeshAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
    TSoftObjectPtr<UAnimSequence> FoxAnimAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
    TSoftObjectPtr<USkeletalMesh> WolfSkeletalMeshAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
    TSoftObjectPtr<UAnimSequence> WolfAnimAsset;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
    TSoftObjectPtr<USkeletalMesh> PigSkeletalMeshAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
    TSoftObjectPtr<UAnimSequence> PigAnimAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
    TSoftObjectPtr<USkeletalMesh> DeerDoeSkeletalMeshAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
    TSoftObjectPtr<UAnimSequence> DeerDoeAnimAsset;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimSequence* CurrentAnimSequence;
    
    virtual void BeginPlay() override;

protected:

	virtual bool ActivatePowerUp(class ABombBotCharacter* PlayerCharacter) override;

};
