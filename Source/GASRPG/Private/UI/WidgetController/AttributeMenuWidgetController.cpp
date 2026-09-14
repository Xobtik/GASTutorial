// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Data/AttributeInfoDataAsset.h"

void UAttributeMenuWidgetController::BrodcastInitalValues()
{
	check(AttributeInfo);
	for (const FRPGAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		BroadcastAttributeInfo(Info);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependancies()
{
	check(AttributeInfo);
	for (const FRPGAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.AttributeGetter).AddLambda(
			[this, &Info](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Info);
			});
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FRPGAttributeInfo& Info) const
{
	FRPGAttributeInfo NewInfo = Info;
	NewInfo.AttributeValue = Info.AttributeGetter.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(NewInfo);
}
