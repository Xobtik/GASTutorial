// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBlueprintFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/RPGPlayerState.h"
#include "UI/WidgetController/RPGWidgetController.h"
#include "UI/HUD/RPGHUD.h"
#include "UI/WidgetController/RPGOverlayWidgetController.h"

URPGOverlayWidgetController* URPGBlueprintFunctionLibrary::GetOverlayWidgetController(	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ARPGHUD* RPGHUD = Cast<ARPGHUD>(PC->GetHUD()))
		{
			ARPGPlayerState* PS = PC->GetPlayerState<ARPGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams Params (PC,PS,ASC,AS);
			return RPGHUD->GetOverlayWidgetController(Params);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* URPGBlueprintFunctionLibrary::GetAttributeWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ARPGHUD* RPGHUD = Cast<ARPGHUD>(PC->GetHUD()))
		{
			ARPGPlayerState* PS = PC->GetPlayerState<ARPGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams Params (PC,PS,ASC,AS);
			return RPGHUD->GetAttributeMenuWidgetController(Params);
		}
	}
	return nullptr;
}
