// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RPGPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/RPGInputComponent.h"
#include "Interaction/TargetInterface.h"

ARPGPlayerController::ARPGPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ARPGPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CursorTrace();
	AutoRun();
}

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(RPGInputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
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

	URPGInputComponent* RPGInputComponent = CastChecked<URPGInputComponent>(InputComponent);
	RPGInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGPlayerController::Move);
	RPGInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &ARPGPlayerController::ShiftPressed);
	RPGInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ARPGPlayerController::ShiftReleased);
	RPGInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
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
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = CursorHit.GetActor();

	if (LastActor != CurrentActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (CurrentActor) CurrentActor->HighlightActor();
	}
}

void ARPGPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	FGameplayTag ComparisonTag = FGameplayTag::RequestGameplayTag(FName(TEXT("InputAction.Primary")));
	if (InputTag.MatchesTagExact(ComparisonTag))
	{
		bTargeting = CurrentActor ? true : false;
		bAutoRunning = false;
	}
}

void ARPGPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	FGameplayTag ComparisonTag = FGameplayTag::RequestGameplayTag(FName(TEXT("InputAction.Primary")));
	
	if (GetASC())
	{
		GetASC()->AbilityInputTagReleased(InputTag);
	}
	
	if (!InputTag.MatchesTagExact(ComparisonTag))
	{
		return;
	}
	
	if (!bTargeting && !bShiftKeyDown)
	{
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}
				if (NavPath->PathPoints.Num() >0 )
				{
					CachedDestination = NavPath->PathPoints.Last();
					bAutoRunning = true;
				}
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void ARPGPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	FGameplayTag ComparisonTag = FGameplayTag::RequestGameplayTag(FName(TEXT("InputAction.Primary")));
	if (!InputTag.MatchesTagExact(ComparisonTag))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	if (bTargeting || bShiftKeyDown)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

URPGAbilitySystemComponent* ARPGPlayerController::GetASC()
{
	if (RPGAbilitySystemComponent == nullptr)
	{
		RPGAbilitySystemComponent = Cast<URPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return RPGAbilitySystemComponent;
}

void ARPGPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
