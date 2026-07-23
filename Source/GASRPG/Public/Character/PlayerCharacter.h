// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGASCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GASRPG_API APlayerCharacter : public ABaseGASCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

};
