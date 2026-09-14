// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"

/**
 * AuraGameplayTags
 *
 */
 
namespace RPGGameplayTags
{
	// Primary
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Strength);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Intelligence);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Resilience);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Vigor);
 
	// Secondary
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Armor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ArmorPenetration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_BlockChance);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitChance);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitDamage);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitResistance);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_HealthRegeneration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ManaRegeneration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxHealth);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxMana);

	//Input
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAction_Primary);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAction_Secondary);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAction_FirstAbility);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAction_SecondAbility);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAction_ThirdAbility);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputAction_FourthAbility);
    
}
