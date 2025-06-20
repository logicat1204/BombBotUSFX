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
#include "Components/SpotLightComponent.h"
#include "World1_Factory.h"
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

	// --- INICIALIZACI�N DE VIDAS ---
	// --- INICIALIZACI�N DE STATS ---
	MaxLives = 3; // Ajustado a 3 vidas
	CurrentLives = MaxLives;
	RespawnDelay = 1.5f; // Por defecto 3 segundos de retraso, puedes cambiarlo en el Blueprint
	// --- FIN DE INICIALIZACI�N DE VIDAS ---

	// Constructor
	bIsImmortal = false;

	//Linterna
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(RootComponent);  // O GetMesh(), seg�n prefieras
	Flashlight->SetRelativeLocation(FVector(50.f, 0.f, 60.f));
	Flashlight->SetIntensity(80000.0f);
	Flashlight->SetInnerConeAngle(20.0f);
	Flashlight->SetOuterConeAngle(40.0f);
	Flashlight->SetVisibility(true);
	Flashlight->SetAttenuationRadius(MaxFlashlightDistance);
    
    // En el constructor o BeginPlay, suscribe la funci�n al evento OnComponentHit
    // El CapsuleComponent es el componente ra�z de ACharacter por defecto
    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABombBotCharacter::OnHitJugador);

    // Aseg�rate de que tu CapsuleComponent est� configurado para generar eventos de hit
    // Esto se puede hacer en el editor o en C++:
    GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
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


		// Looking
		EnhancedInputComponent->BindAction(PausarJuego, ETriggerEvent::Started, this, &ABombBotCharacter::PausarElJuego);
		// Colocar bomba
		// Controles creados
		// Colocar Bomba

		//Colocamos Started para que solo lea la primera vez que se presiona el boton
		EnhancedInputComponent->BindAction(TurnFlashlightAction, ETriggerEvent::Started, this, &ABombBotCharacter::Flash);

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

		// Evitar que se procese da�o si ya estamos en el proceso de respawn
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
				OnDeath_Implementation(); // Llamar a la funci�n de muerte
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
	// Aqu� podr�as llamar a una funci�n en tu GameMode para manejar el Game Over globalmente.
	// AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	// if (MyCustomGameMode* CustomGameMode = Cast<MyCustomGameMode>(GameMode))
	// {
	//    CustomGameMode->HandlePlayerDeath();
	// }

	// O simplemente salir del juego (para pruebas r�pidas):
	// UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);

	// O mostrar un widget de Game Over y esperar input para reiniciar o salir.
}

void ABombBotCharacter::Respawn()
{
	UE_LOG(LogTemp, Log, TEXT("my_characterCharacter: Reapareciendo..."));

	// Aseg�rate de que el personaje tenga un controlador v�lido.
	AController* MyController = GetController();
	if (MyController)
	{
		// Opci�n 1: Simplemente teletransportar el actor existente.
		SetActorLocationAndRotation(InitialSpawnLocation, InitialSpawnRotation, false, nullptr, ETeleportType::TeleportPhysics);

		// Reiniciar el estado del movimiento si es necesario (ej. velocidad)
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		GetCharacterMovement()->StopMovementImmediately(); // Detener cualquier movimiento residual

		// Si el personaje fue deshabilitado de alguna forma (ej. en OnDeath si no se destruye)
		// necesitar�as reactivarlo aqu�.
		// EnableInput(Cast<APlayerController>(MyController));
		// GetCharacterMovement()->SetMovementMode(MOVE_Walking); // o el modo por defecto
		// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("my_characterCharacter: No se puede reaparecer, no tiene controlador."));
	}

	// Tambi�n podr�as solicitar al GameMode que se encargue del respawn,
	// lo que permitir�a m�s flexibilidad (ej. elegir entre varios puntos de spawn).
	// AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	// if (GameMode)
	// {
	//    GameMode->RestartPlayer(MyController); // Esto reaparecer� al jugador en un PlayerStart
	// }
	// Para usar RestartPlayer, necesitar�as tener un Actor PlayerStart en tu nivel.
	// Si solo quieres volver a la posici�n inicial guardada, el SetActorLocationAndRotation es suficiente.
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
	// GetCharacterMovement()->DisableMovement(); // Podr�as deshabilitar el movimiento completamente tambi�n

	// Opcional: Podr�as poner al personaje en un estado "aturdido", reproducir una animaci�n, etc.
	// Por ejemplo, desactivar colisiones para que no reciba m�s da�o mientras espera
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

	Respawn(); // Ahora llamamos a la funci�n de respawn original
}

void ABombBotCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Asignamos el widget al character.
	AsignWidget();
	// Guardar la posici�n y rotaci�n inicial al comenzar el juego
	InitialSpawnLocation = GetActorLocation();
	InitialSpawnRotation = GetActorRotation();

	CurrentLives = MaxLives; // Asegurarse de que las vidas est�n al m�ximo al empezar/reiniciar nivel
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
	// Aqu� podr�as activar/desactivar efectos visuales de inmortalidad
	if (bIsImmortal)
	{
		UE_LOG(LogTemp, Log, TEXT("Personaje AHORA ES INMORTAL"));
		// Ejemplo: Cambiar color del material, activar part�culas, etc.
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

	if (LifeUI)
	{
		LifeUI->RecuperarVida();
	}
	CurrentLives += Amount;
	if (CurrentLives > MaxLives)
	{
		CurrentLives = MaxLives; // No exceder el m�ximo de vidas
	}
	UE_LOG(LogTemp, Log, TEXT("Vidas recuperadas. Vidas actuales: %d"), CurrentLives);
	// Aqu� podr�as actualizar un HUD si tienes uno
}

void ABombBotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
//    //Dibujar la capsula
//    DrawDebugCapsule(GetWorld(), GetCapsuleComponent()->GetComponentLocation(),
//                     GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
//                     GetCapsuleComponent()->GetScaledCapsuleRadius(),
//                     GetCapsuleComponent()->GetComponentQuat(),
//                     FColor::Green, false, 0.1f, 0, 2.0f);
    
	DetectCloseBomb();

	//Linterna
	 // Trazar hacia donde apunta la linterna
	FVector Start = Flashlight->GetComponentLocation();
	FVector End = Start + Flashlight->GetForwardVector() * MaxFlashlightDistance;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignora al personaje

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	float FinalDistance = MaxFlashlightDistance;

	if (bHit)
	{
		FinalDistance = (Hit.Location - Start).Size();
	}
}

void ABombBotCharacter::ColocarBomba()
{
	if (GetWorld())
	{
		// Verificar si hay alguna bomba cerca de la posici�n actual antes de colocar
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
				LastPlacedBomb = NewBomb; // Actualizar la referencia a la �ltima bomba

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
	// Limpiar bombas inv�lidas del array
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

	// Verificar si el jugador est� cerca de alguna bomba
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

	// Solo permitir colocar bomba si el jugador NO est� cerca de ninguna bomba
	CanPlace = !bPlayerNearBomb;
}

void ABombBotCharacter::OnBombDestroyed(AActor* DestroyedActor)
{
	ABomba* DestroyedBomb = Cast<ABomba>(DestroyedActor);
	if (DestroyedBomb)
	{
		// Remover la bomba del array
		PlacedBombs.Remove(DestroyedBomb);

		// Si era la �ltima bomba colocada, resetear la referencia
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
	float MinDistance = 150.0f; // Distancia m�nima entre bombas

	// Verificar todas las bombas colocadas
	for (int32 i = PlacedBombs.Num() - 1; i >= 0; i--)
	{
		if (PlacedBombs[i] == nullptr || !IsValid(PlacedBombs[i]))
		{
			// Remover bombas inv�lidas del array
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

void ABombBotCharacter::PausarElJuego()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	// Usar el estado de pausa del mundo
	bool bIsGamePaused = UGameplayStatics::IsGamePaused(GetWorld());

	if (!bIsGamePaused)
	{
		// Crear el widget si a�n no existe
		if (WidgetPausaClass && !WidgetPausaInstance)
		{
			WidgetPausaInstance = CreateWidget<UUserWidget>(PC, WidgetPausaClass);
		}

		if (WidgetPausaInstance)
		{
			WidgetPausaInstance->AddToViewport();

			// Pausar el juego
			UGameplayStatics::SetGamePaused(GetWorld(), true);

			// Mostrar el cursor y permitir input del UI
			PC->bShowMouseCursor = true;
			FInputModeUIOnly InputMode;
			PC->SetInputMode(InputMode);
		}
	}
	else
	{
		// Reanudar el juego
		if (WidgetPausaInstance)
		{
			WidgetPausaInstance->RemoveFromParent();
		}

		UGameplayStatics::SetGamePaused(GetWorld(), false);
		PC->bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
	}
}

//Con este metodo podemos agregar puntaje al GameInstance.
void ABombBotCharacter::AddScore(int32 Amount)
{
	if (LifeUI)
	{
		LifeUI->AumentarScore(Amount);
	}
}

void ABombBotCharacter::ActivateSpeedBoost(float Multiplier, float Duration)
{
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (!MoveComp) return;

	// Si ya hay un boost activo, lo reseteamos antes de aplicar el nuevo.
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_SpeedBoost);

	// Solo guardamos la velocidad original si no ten�amos ya un boost activo.
	if (!bIsSpeedBoosted)
	{
		OriginalMaxWalkSpeed = MoveComp->MaxWalkSpeed;
		bIsSpeedBoosted = true;
	}

	// Aplicamos el nuevo multiplicador a la velocidad original guardada
	MoveComp->MaxWalkSpeed = OriginalMaxWalkSpeed * Multiplier;

	UE_LOG(LogTemp, Log, TEXT("SPEED BOOST ACTIVADO. Nueva velocidad: %f"), MoveComp->MaxWalkSpeed);

	// Iniciamos el temporizador para desactivar el boost
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpeedBoost, this, &ABombBotCharacter::DeactivateSpeedBoost, Duration, false);
}

void ABombBotCharacter::DeactivateSpeedBoost()
{
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (!MoveComp) return;

	// Restauramos la velocidad a su valor original
	MoveComp->MaxWalkSpeed = OriginalMaxWalkSpeed;
	bIsSpeedBoosted = false; // Marcamos que el boost ya no est� activo

	UE_LOG(LogTemp, Log, TEXT("SPEED BOOST TERMINADO. Velocidad restaurada a: %f"), MoveComp->MaxWalkSpeed);
}

void ABombBotCharacter::ActivateImmortality(float Duration)
{
	// Si ya somos inmortales, simplemente reseteamos la duraci�n del efecto.
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Immortality);

	// Activamos la inmortalidad
	SetImmortality(true);

	// Iniciamos el temporizador para desactivarla
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Immortality, this, &ABombBotCharacter::DeactivateImmortality, Duration, false);
}

void ABombBotCharacter::DeactivateImmortality()
{
	// Simplemente llamamos a la funci�n que ya ten�as para desactivar el estado.
	SetImmortality(false);
}

//Linterna
void ABombBotCharacter::Flash(const FInputActionValue& Value)
{
	if (Value.Get<bool>()) {
		Flashlight->ToggleVisibility();
	}
	else {
		Flashlight->ToggleVisibility();
	}
}

void ABombBotCharacter::setFabrica(AWorld1_Factory* NuevaFabrica)
{
	
	FabricaW1 = NuevaFabrica;
}

void ABombBotCharacter::OpenEscapeDoor()
{
	if (!FabricaW1) return;
	if (Personas == Meta) {
		FabricaW1->CreateExit();
	}
	else {
		// llamar metodo para destruir el bloque�puerta
		Personas++;
	}
}

void ABombBotCharacter::OnHitJugador(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor == this)
    {
        UE_LOG(LogTemp, Warning, TEXT("El enemigo toco al jugador!"));

        // Intentar castear el OtherActor a tu clase de personaje
        ABombBotCharacter* PlayerCharacter = Cast<ABombBotCharacter>(OtherActor);

        if (PlayerCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Enemigo toco a: %s"), *PlayerCharacter->GetName());
            // Llamar a la funci�n para que el jugador pierda una vida
            this->TakeDamageAndLoseLife();

            // Aqu� podr�as anadir logica adicional para el enemigo, como:
            // - Destruirse a si mismo despu�s de da�ar al jugador: Destroy();
            // - Desactivar su colisi�n por un tiempo para no da�ar repetidamente:
            //   CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            //   FTimerHandle TempTimer;
            //   GetWorldTimerManager().SetTimer(TempTimer, [this]() { if(CollisionComp) CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly); }, 2.0f, false);
        }
    }
}
