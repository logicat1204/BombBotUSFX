// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombBotCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TimerManager.h" // Necesario para FTimerManager
#include "Engine/World.h"   // Necesario para GetWorld()
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Bomba/Bomba.h"

#include "BombBotGameInstance.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ABombBotCharacter

ABombBotCharacter::ABombBotCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// --- INICIALIZACIÓN DE VIDAS ---
	// --- INICIALIZACIÓN DE STATS ---
	MaxLives = 3; // Ajustado a 3 vidas
	CurrentLives = MaxLives;
	RespawnDelay = 3.0f; // Por defecto 3 segundos de retraso, puedes cambiarlo en el Blueprint
	// --- FIN DE INICIALIZACIÓN DE VIDAS ---

	// Constructor
	bIsImmortal = false;

}

//////////////////////////////////////////////////////////////////////////
// Input

void ABombBotCharacter::AsignWidget()
{
	//Aqui asigno el HUD que tiene el Character.
	if (LifeUIClass)
	{
		LifeUI = CreateWidget<UWUI_Principal>(GetWorld(), LifeUIClass);
		if (LifeUI)
		{
			LifeUI->AddToViewport();
		}
	}
}

void ABombBotCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ABombBotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABombBotCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABombBotCharacter::Look);

		// Colocar bomba
		// Controles creados
		// Colocar Bomba

		if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInput->BindAction(SetBomb, ETriggerEvent::Triggered, this, &ABombBotCharacter::ColocarBomba);
		}

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABombBotCharacter::TakeDamageAndLoseLife()
{
	if (bIsImmortal)
	{
		UE_LOG(LogTemp, Log, TEXT("ABomberMan_012025Character: Jugador toco enemigo PERO ES INMORTAL. No se pierde vida."));
		//return;
	}
	else {

		// Evitar que se procese daño si ya estamos en el proceso de respawn
		if (GetWorldTimerManager().IsTimerActive(TimerHandle_RespawnDelay))
		{
			UE_LOG(LogTemp, Log, TEXT("ABomberMan_012025Character: Dano ignorado, ya en proceso de respawn."));
			return;
		}

		if (LifeUI)
		{
			LifeUI->ReducirVida();
		}
		if (CurrentLives > 0)
		{
			CurrentLives--;
			UE_LOG(LogTemp, Log, TEXT("ABomberMan_012025Character: Vida perdida. Vidas restantes: %d"), CurrentLives);

			if (CurrentLives <= 0)
			{
				OnDeath_Implementation(); // Llamar a la función de muerte
			}
			else
			{
				// En lugar de llamar a Respawn() directamente, iniciamos el proceso con retraso
				StartRespawnProcess();
			}
		}
	}
}

void ABombBotCharacter::OnDeath_Implementation()
{

	if (GameOverWidgetClass)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			// Crear y mostrar el widget
			GameOverWidget = CreateWidget<UUserWidget>(PlayerController, GameOverWidgetClass);
			if (GameOverWidget)
			{
				GameOverWidget->AddToViewport();

				// Opcional: detener entrada del jugador
				PlayerController->SetPause(true);
				PlayerController->bShowMouseCursor = true;
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(GameOverWidget->TakeWidget());
				PlayerController->SetInputMode(InputMode);
			}
		}
	}
	// Aquí podrías llamar a una función en tu GameMode para manejar el Game Over globalmente.
	// AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	// if (MyCustomGameMode* CustomGameMode = Cast<MyCustomGameMode>(GameMode))
	// {
	//    CustomGameMode->HandlePlayerDeath();
	// }

	// O simplemente salir del juego (para pruebas rápidas):
	// UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);

	// O mostrar un widget de Game Over y esperar input para reiniciar o salir.
}

void ABombBotCharacter::Respawn()
{
	UE_LOG(LogTemp, Log, TEXT("my_characterCharacter: Reapareciendo..."));

	// Asegúrate de que el personaje tenga un controlador válido.
	AController* MyController = GetController();
	if (MyController)
	{
		// Opción 1: Simplemente teletransportar el actor existente.
		SetActorLocationAndRotation(InitialSpawnLocation, InitialSpawnRotation, false, nullptr, ETeleportType::TeleportPhysics);

		// Reiniciar el estado del movimiento si es necesario (ej. velocidad)
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		GetCharacterMovement()->StopMovementImmediately(); // Detener cualquier movimiento residual

		// Si el personaje fue deshabilitado de alguna forma (ej. en OnDeath si no se destruye)
		// necesitarías reactivarlo aquí.
		// EnableInput(Cast<APlayerController>(MyController));
		// GetCharacterMovement()->SetMovementMode(MOVE_Walking); // o el modo por defecto
		// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("my_characterCharacter: No se puede reaparecer, no tiene controlador."));
	}

	// También podrías solicitar al GameMode que se encargue del respawn,
	// lo que permitiría más flexibilidad (ej. elegir entre varios puntos de spawn).
	// AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	// if (GameMode)
	// {
	//    GameMode->RestartPlayer(MyController); // Esto reaparecerá al jugador en un PlayerStart
	// }
	// Para usar RestartPlayer, necesitarías tener un Actor PlayerStart en tu nivel.
	// Si solo quieres volver a la posición inicial guardada, el SetActorLocationAndRotation es suficiente.
}

void ABombBotCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABombBotCharacter::Look(const FInputActionValue& Value)
{

}

void ABombBotCharacter::StartRespawnProcess()
{
	UE_LOG(LogTemp, Log, TEXT("ABomberMan_012025Character: Iniciando proceso de respawn con retraso."));

	// 1. Desactivar input del jugador
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		DisableInput(PC);
	}

	// Opcional: Detener movimiento inmediatamente
	GetCharacterMovement()->StopMovementImmediately();
	// GetCharacterMovement()->DisableMovement(); // Podrías deshabilitar el movimiento completamente también

	// Opcional: Podrías poner al personaje en un estado "aturdido", reproducir una animación, etc.
	// Por ejemplo, desactivar colisiones para que no reciba más daño mientras espera
	// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	// 2. Iniciar el temporizador para el respawn
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(TimerHandle_RespawnDelay, this, &ABombBotCharacter::DelayedRespawn, RespawnDelay, false);
	}
}

void ABombBotCharacter::DelayedRespawn()
{
	UE_LOG(LogTemp, Log, TEXT("ABomberMan_012025Character: Timer de retraso completado. Ejecutando Respawn()."));

	// Antes de reaparecer, reactivar input y colisiones si se desactivaron
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		EnableInput(PC);
	}
	// GetCharacterMovement()->SetMovementMode(MOVE_Walking); // O el modo por defecto
	// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Respawn(); // Ahora llamamos a la función de respawn original
}

void ABombBotCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Asignamos el widget al character.
	AsignWidget();
	// Guardar la posición y rotación inicial al comenzar el juego
	InitialSpawnLocation = GetActorLocation();
	InitialSpawnRotation = GetActorRotation();

	CurrentLives = MaxLives; // Asegurarse de que las vidas estén al máximo al empezar/reiniciar nivel
	UE_LOG(LogTemp, Log, TEXT("my_characterCharacter: Vidas iniciales: %d"), CurrentLives);

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
	}
}

void ABombBotCharacter::SetImmortality(bool bNewImmortalityState)
{
	bIsImmortal = bNewImmortalityState;
	// Aquí podrías activar/desactivar efectos visuales de inmortalidad
	if (bIsImmortal)
	{
		UE_LOG(LogTemp, Log, TEXT("Personaje AHORA ES INMORTAL"));
		// Ejemplo: Cambiar color del material, activar partículas, etc.
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Personaje YA NO ES INMORTAL"));
		// Revertir efectos visuales
	}
}

bool ABombBotCharacter::IsImmortal() const
{
	return bIsImmortal;
}

void ABombBotCharacter::RecoverLives(int32 Amount)
{
	if (Amount <= 0) return;

	CurrentLives += Amount;
	if (CurrentLives > MaxLives)
	{
		CurrentLives = MaxLives; // No exceder el máximo de vidas
	}
	UE_LOG(LogTemp, Log, TEXT("Vidas recuperadas. Vidas actuales: %d"), CurrentLives);
	// Aquí podrías actualizar un HUD si tienes uno
}

void ABombBotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DetectCloseBomb();
}

void ABombBotCharacter::ColocarBomba()
{
	if (GetWorld())
	{
		// Verificar si hay alguna bomba cerca de la posición actual antes de colocar
		if (!CanPlaceBombAtCurrentLocation())
		{
			UE_LOG(LogTemplateCharacter, Warning, TEXT("Cannot place bomb: There's already a bomb too close!"));
			return;
		}

		if (CanPlace == true&&inv_bombas>0)
		{
			LifeUI->ReducirBombas();
			inv_bombas--;
			FVector SpawnLocation = GetActorLocation() + FVector(0, 0, -90); // Adjust spawn location above the character
			FRotator SpawnRotation = GetActorRotation();

			// Spawn the bomb actor
			ABomba* NewBomb = GetWorld()->SpawnActor<ABomba>(ABomba::StaticClass(), SpawnLocation, SpawnRotation);
			if (NewBomb)
			{
				NewBomb->OnDestroyed.AddDynamic(this, &ABombBotCharacter::OnBombDestroyed);
				PlacedBombs.Add(NewBomb);
				LastPlacedBomb = NewBomb; // Actualizar la referencia a la última bomba

				// Desactivar temporalmente la capacidad de colocar bombas
				CanPlace = false;

				UE_LOG(LogTemplateCharacter, Log, TEXT("Bomb placed successfully. Total bombs: %d"), PlacedBombs.Num());
			}
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Warning, TEXT("You can only place one bomb at a time!"));
		}
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to spawn bomb: World is null"));
	}
}

void ABombBotCharacter::ReloadBombs()
{
	if (inv_bombas <= 3)
	{
		inv_bombas++;
		LifeUI->AumentarBombas();
	}
}

void ABombBotCharacter::DetectCloseBomb()
{
	// Limpiar bombas inválidas del array
	for (int32 i = PlacedBombs.Num() - 1; i >= 0; i--)
	{
		if (PlacedBombs[i] == nullptr || !IsValid(PlacedBombs[i]))
		{
			PlacedBombs.RemoveAt(i);
		}
	}

	// Si no hay bombas, permitir colocar
	if (PlacedBombs.Num() == 0)
	{
		CanPlace = true;
		LastPlacedBomb = nullptr;
		return;
	}

	// Verificar si el jugador está cerca de alguna bomba
	FVector PlayerLocation = GetActorLocation();
	bool bPlayerNearBomb = false;

	for (ABomba* Bomb : PlacedBombs)
	{
		if (Bomb && IsValid(Bomb))
		{
			FVector BombLocation = Bomb->GetActorLocation();
			float Distance = FVector::Dist(PlayerLocation, BombLocation);

			if (Distance < 150.0f)
			{
				bPlayerNearBomb = true;
				LastPlacedBomb = Bomb;
				break;
			}
		}
	}

	// Solo permitir colocar bomba si el jugador NO está cerca de ninguna bomba
	CanPlace = !bPlayerNearBomb;
}

void ABombBotCharacter::OnBombDestroyed(AActor* DestroyedActor)
{
	ABomba* DestroyedBomb = Cast<ABomba>(DestroyedActor);
	if (DestroyedBomb)
	{
		// Remover la bomba del array
		PlacedBombs.Remove(DestroyedBomb);

		// Si era la última bomba colocada, resetear la referencia
		if (DestroyedActor == LastPlacedBomb)
		{
			LastPlacedBomb = nullptr;
		}

		// Verificar si ahora se puede colocar una bomba
		if (PlacedBombs.Num() == 0 || CanPlaceBombAtCurrentLocation())
		{
			CanPlace = true;
		}

		UE_LOG(LogTemplateCharacter, Log, TEXT("Bomb destroyed. Remaining bombs: %d"), PlacedBombs.Num());
	}
	ReloadBombs();
}

bool ABombBotCharacter::CanPlaceBombAtCurrentLocation()
{
	FVector PlayerLocation = GetActorLocation();
	float MinDistance = 150.0f; // Distancia mínima entre bombas

	// Verificar todas las bombas colocadas
	for (int32 i = PlacedBombs.Num() - 1; i >= 0; i--)
	{
		if (PlacedBombs[i] == nullptr || !IsValid(PlacedBombs[i]))
		{
			// Remover bombas inválidas del array
			PlacedBombs.RemoveAt(i);
			continue;
		}

		FVector BombLocation = PlacedBombs[i]->GetActorLocation();
		float Distance = FVector::Dist(PlayerLocation, BombLocation);

		if (Distance < MinDistance)
		{
			return false; // Hay una bomba muy cerca
		}
	}

	return true; // No hay bombas cerca, se puede colocar
}

//Con este metodo podemos agregar puntaje al GameInstance.
void ABombBotCharacter::AddScore(int32 Amount)
{
	UBombBotGameInstance* GameInstance = Cast<UBombBotGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->AddScore(Amount);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to add score: GameInstance is null"));
	}
}
