// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DamageMatrixDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UDamageMatrixDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Matrix")
	TMap<FGameplayTag, FGameplayTag> DamageToResistanceMap;
};
