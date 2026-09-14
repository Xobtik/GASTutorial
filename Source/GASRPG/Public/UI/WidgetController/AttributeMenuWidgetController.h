// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/RPGWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfoDataAsset;
struct FGameplayTag;
struct FRPGAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FRPGAttributeInfo&, Info);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GASRPG_API UAttributeMenuWidgetController : public URPGWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BrodcastInitalValues() override;
	virtual void BindCallbacksToDependancies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfoDataAsset> AttributeInfo;
	
private:
	void BroadcastAttributeInfo(const FRPGAttributeInfo& Info) const;
};
