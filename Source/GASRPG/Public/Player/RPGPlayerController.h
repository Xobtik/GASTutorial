// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

class ITargetInterface;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class GASRPG_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARPGPlayerController();

	virtual void Tick(float DeltaSeconds) override;

protected:	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> RPGInputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	TScriptInterface<ITargetInterface> LastActor;
	TScriptInterface<ITargetInterface> CurrentActor;
};
