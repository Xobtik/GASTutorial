// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGASCharacter.h"
#include "Interaction/TargetInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class GASRPG_API AEnemyCharacter : public ABaseGASCharacter, public ITargetInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;
	
};
