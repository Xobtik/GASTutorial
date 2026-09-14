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

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
	
protected:
	virtual void BeginPlay() override;

private:
	virtual void InitPlayerDetails() override;
	

};
