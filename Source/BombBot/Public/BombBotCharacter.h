// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Blueprint/UserWidget.h"
#include "BombBot/Display/WUI_Principal.h"
#include "BombBotCharacter.generated.h"
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class ABomba;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class ABombBotCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	

	// Controles personalizados:
	/** Colocar bomba */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetBomb;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PausarJuego;

public:
	ABombBotCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    UFUNCTION()
    void OnHitJugador(UPrimitiveComponent* HitComp, AActor* OtherActor,
                      UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// Timer para el retraso del respawn
	FTimerHandle TimerHandle_RespawnDelay; // Renombrado de RespawnTimerHandle para claridad
	/* Metodos mecanica bomba */
	void ColocarBomba();

	void ReloadBombs();

	void DetectCloseBomb();
	//Se le debe colocar como UFUNCTION para que el sistema de reconocimiento de UE funcione :D
	UFUNCTION()
	void OnBombDestroyed(AActor* DestroyedActor);

	bool CanPlaceBombAtCurrentLocation();

	void PausarElJuego();

protected:
	TArray<ABomba*> PlacedBombs;
	bool CanPlace = true;
	//Variable global para controlar la distancia de la ultima bomba colocada.
	class ABomba* LastPlacedBomb = nullptr;
	//Con esta propiedad ajustamos la cantidad de bombas que puede colocar el jugador.
	UPROPERTY(EditAnywhere)
	int32 inv_bombas=3;
public:

	/* Metodos puntuacion */
	void AddScore(int32 Amount);

	// Clase del widget (settable en el editor)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UWUI_Principal> LifeUIClass;

	// Instancia del widget
	UPROPERTY()
	UWUI_Principal* LifeUI;

	void AsignWidget();
protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// --- STATS DEL JUGADOR ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int32 MaxLives;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerStats")
	int32 CurrentLives;

	// --- FUNCIONES DE DAÑO, MUERTE Y RESPAWN ---
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	void TakeDamageAndLoseLife();

	void OnDeath_Implementation();

	UFUNCTION(BlueprintCallable, Category = "PlayerActions")
	void Respawn();

	// --- NUEVAS ADICIONES PARA EL RETRASO DE RESPAWN ---
	UPROPERTY(EditDefaultsOnly, Category = "PlayerStats", meta = (ClampMin = "0.0"))
	float RespawnDelay; // Tiempo en segundos antes de reaparecer después de perder una vida

protected:
	// --- FUNCIONES DE RESPAWN CON RETRASO ---
	void StartRespawnProcess(); // Inicia el proceso de desactivación y el timer
	void DelayedRespawn();      // Función llamada por el timer para ejecutar Respawn()
	virtual void BeginPlay() override;

	bool bIsImmortal;

	FVector InitialSpawnLocation;
	FRotator InitialSpawnRotation;

public:
	// --- FUNCIONES PARA POWER-UPS ---
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	void SetImmortality(bool bNewImmortalityState);

	UFUNCTION(BlueprintPure, Category = "PlayerStats")
	bool IsImmortal() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	void RecoverLives(int32 Amount);

	//Widget Game Over
public:
	// Clase del widget que se usara para el Game Over
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	// Referencia al widget mostrado
	UPROPERTY()
	UUserWidget* GameOverWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> WidgetPausaClass;

	UFUNCTION(BlueprintCallable, Category = "PowerUps")
	void ActivateSpeedBoost(float Multiplier, float Duration);

	/** Activa la inmortalidad temporal en el personaje. */
	UFUNCTION(BlueprintCallable, Category = "PowerUps")
	void ActivateImmortality(float Duration);

private:
	UUserWidget* WidgetPausaInstance;

	/** Revierte el efecto del aumento de velocidad. */
	void DeactivateSpeedBoost();

	/** Revierte el efecto de inmortalidad (aunque podemos reusar SetImmortality). */
	void DeactivateImmortality();

	// --- NUEVAS VARIABLES PARA GESTIONAR ESTADOS ---

	/** Guarda la velocidad de caminar original del personaje antes del boost. */
	float OriginalMaxWalkSpeed;

	/** Un flag para saber si el boost de velocidad está activo. */
	bool bIsSpeedBoosted;

	/** Handles para los temporizadores de los efectos. */
	FTimerHandle TimerHandle_SpeedBoost;
	FTimerHandle TimerHandle_Immortality;
	public:
	//Linterna
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flashlight")
	class USpotLightComponent* Flashlight;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* TurnFlashlightAction;

	// Alcance máximo de la linterna
	UPROPERTY(EditAnywhere, Category = "Linterna")
	float MaxFlashlightDistance = 500.0f;

	private:
	void Flash(const FInputActionValue& Value);


};
