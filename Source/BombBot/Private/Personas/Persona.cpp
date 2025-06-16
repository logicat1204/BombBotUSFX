// Fill out your copyright notice in the Description page of Project Settings.


#include "Personas/Persona.h"

// PowerUp_Velocidad.cpp
// Fill out your copyright notice in the Description page of Project Settings.

#include "BombBotCharacter.h"
#include "Engine/StreamableManager.h" // Necesario para la carga asíncrona
#include "Engine/AssetManager.h"      // Necesario para el AssetManager

APersona::APersona()
{
    
    PrimaryActorTick.bCanEverTick = true;
    
    // Crear el componente de Skeletal Mesh
    MiSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MiSkeletalMeshComponent"));
    
    // Establecerlo como el RootComponent si es el único componente visual y quieres que defina la posición del actor
    SetRootComponent(MiSkeletalMesh);
    PowerUpCollision->SetupAttachment(MiSkeletalMesh);
    
    // Opcional: Cargar un Skeletal Mesh por defecto directamente en C++
    // Esto es útil si siempre quieres el mismo mesh, pero a menudo es mejor asignarlo en Blueprint.
    // Aquí asignarías las rutas a tus TSoftObjectPtr
    // Esto se puede hacer en el constructor o directamente en Blueprint
    FoxSkeletalMeshAsset = TSoftObjectPtr<USkeletalMesh>(FSoftObjectPath(TEXT("/Game/AnimalVarietyPack/Fox/Meshes/SK_Fox.SK_Fox")));
    FoxAnimAsset = TSoftObjectPtr<UAnimSequence>(FSoftObjectPath(TEXT("/Game/AnimalVarietyPack/Fox/Animations/ANIM_Fox_IdleLookAround.ANIM_Fox_IdleLookAround")));
    
    WolfSkeletalMeshAsset = TSoftObjectPtr<USkeletalMesh>(FSoftObjectPath(TEXT("/Game/AnimalVarietyPack/Wolf/Meshes/SK_Wolf.SK_Wolf")));
    WolfAnimAsset = TSoftObjectPtr<UAnimSequence>(FSoftObjectPath(TEXT("/Game/AnimalVarietyPack/Wolf/Animations/ANIM_Wolf_IdleLookAround.ANIM_Wolf_IdleLookAround")));
    
    PigSkeletalMeshAsset = TSoftObjectPtr<USkeletalMesh>(FSoftObjectPath(TEXT("/Game/AnimalVarietyPack/Pig/Meshes/SK_Pig.SK_Pig")));
    PigAnimAsset = TSoftObjectPtr<UAnimSequence>(FSoftObjectPath(TEXT("/Game/AnimalVarietyPack/Pig/Animations/ANIM_Pig_IdleLookAround.ANIM_Pig_IdleLookAround")));
    
    DeerDoeSkeletalMeshAsset = TSoftObjectPtr<USkeletalMesh>(FSoftObjectPath(TEXT("/Game/AnimalVarietyPack/DeerStagAndDoe/Meshes/SK_DeerDoe.SK_DeerDoe")));
    DeerDoeAnimAsset = TSoftObjectPtr<UAnimSequence>(FSoftObjectPath(TEXT("/Game/AnimalVarietyPack/DeerStagAndDoe/Animations/ANIM_DeerDoe_IdleLookAround.ANIM_DeerDoe_IdleLookAround")));

    // ******* LÍNEA CLAVE PARA DESHABILITAR LA ROTACIÓN *******
    if (RotatingMovement) // Verifica que el componente heredado existe
    {
        RotatingMovement->bAutoActivate = false; // Evita que empiece a girar automáticamente
        RotatingMovement->Deactivate(); // Asegura que está desactivado si ya se activó
    }
}
void APersona::BeginPlay() {
    Super::BeginPlay();
    int random = FMath::RandRange(0, 100);
    if (random > 75)
    {
        // Cargar el zorro
        if (FoxSkeletalMeshAsset.IsValid()) // Comprueba si la ruta es válida
        {
            MiSkeletalMesh->SetSkeletalMesh(FoxSkeletalMeshAsset.LoadSynchronous()); // Carga síncrona, puede causar un pequeño hitch
            CurrentAnimSequence = FoxAnimAsset.LoadSynchronous(); // Carga síncrona
        }
    }else if(random > 50){
        // Cargar el lobo
        if (WolfSkeletalMeshAsset.IsValid())
        {
            MiSkeletalMesh->SetSkeletalMesh(WolfSkeletalMeshAsset.LoadSynchronous());
            CurrentAnimSequence = WolfAnimAsset.LoadSynchronous();
        }
    }else if(random > 25){
        // Cargar el cerdo
        if (PigSkeletalMeshAsset.IsValid())
        {
            MiSkeletalMesh->SetSkeletalMesh(PigSkeletalMeshAsset.LoadSynchronous());
            CurrentAnimSequence = PigAnimAsset.LoadSynchronous();
        }
    }else{
        // Cargar el ciervo
        if (DeerDoeSkeletalMeshAsset.IsValid())
        {
            MiSkeletalMesh->SetSkeletalMesh(DeerDoeSkeletalMeshAsset.LoadSynchronous());
            CurrentAnimSequence = DeerDoeAnimAsset.LoadSynchronous();
        }
    }
    
    if (MiSkeletalMesh && CurrentAnimSequence)
    {
        MiSkeletalMesh->PlayAnimation(CurrentAnimSequence, true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No se ha podido cargar el Skeletal Mesh o la animacion para APersona."));
    }
}

bool APersona::ActivatePowerUp(ABombBotCharacter* PlayerCharacter)
{
    Super::ActivatePowerUp(PlayerCharacter);

    if (PlayerCharacter)
    {
        PlayerCharacter->OpenEscapeDoor();

        return true;
    }

    return false;
}
