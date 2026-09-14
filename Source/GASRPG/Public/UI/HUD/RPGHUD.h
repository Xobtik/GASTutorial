// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPGHUD.generated.h"

class UAttributeMenuWidgetController;
struct FWidgetControllerParams;
class URPGUserWidget;
class UAttributeSet;
class UAbilitySystemComponent;
class URPGOverlayWidgetController;


/**
 * 
 */
UCLASS()
class GASRPG_API ARPGHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	
	URPGOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);


protected:

private:
	UPROPERTY()
	TObjectPtr<URPGUserWidget>  OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<URPGUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<URPGOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<URPGOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeWidgetControllerClass;
};
