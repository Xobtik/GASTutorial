// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/DamageMatrixDataAsset.h"
#include "Subsystems/WorldSubsystem.h"
#include "RPGDamageSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API URPGDamageSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UFUNCTION(BlueprintPure, Category = "Damage Subsystem")
	UDamageMatrixDataAsset* GetDamageMatrixAsset() const { return DamageMatrixAsset; }

private:
	UPROPERTY()
	TObjectPtr<UDamageMatrixDataAsset> DamageMatrixAsset;
};
