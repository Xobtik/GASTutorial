// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/DamageMatrixDataAsset.h"
#include "Engine/DeveloperSettings.h"
#include "RPGDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta=(DisplayName="Combat Matrix"))
class GASRPG_API URPGDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	URPGDeveloperSettings() { CategoryName = TEXT("Game"); }

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Damage Rules")
	TSoftObjectPtr<UDamageMatrixDataAsset> GlobalDamageMatrix;
};
