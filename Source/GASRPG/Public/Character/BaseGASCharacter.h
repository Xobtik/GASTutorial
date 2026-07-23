// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseGASCharacter.generated.h"

UCLASS()
class GASRPG_API ABaseGASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseGASCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
