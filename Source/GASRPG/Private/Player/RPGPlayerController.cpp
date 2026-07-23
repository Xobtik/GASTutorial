// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RPGPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/TargetInterface.h"

ARPGPlayerController::ARPGPlayerController()
{
	bReplicates = true;
}

void ARPGPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CursorTrace();
}

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(RPGInputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem)
	Subsystem->AddMappingContext(RPGInputContext,0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	
}

void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGPlayerController::Move);
}

void ARPGPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator YawRotation (0.f, GetControlRotation().Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
	
}

void ARPGPlayerController::CursorTrace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (!Hit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = Hit.GetActor();

	if (LastActor == nullptr)
	{
		if (CurrentActor != nullptr)
		{
			CurrentActor->HighlightActor();
		}
	}
	else
	{
		if (CurrentActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != CurrentActor)
			{
				
				LastActor->UnHighlightActor();
				CurrentActor->HighlightActor();
			}
		}
	}
}
