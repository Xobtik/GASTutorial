// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGDamageSubsystem.h"

#include "RPGDeveloperSettings.h"

void URPGDamageSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	if (InWorld.IsGameWorld())
	{
		if (const URPGDeveloperSettings* Settings = GetDefault<URPGDeveloperSettings>())
		{
			if (!Settings->GlobalDamageMatrix.IsNull())
			{
				DamageMatrixAsset = Settings->GlobalDamageMatrix.LoadSynchronous();
			}
		}
	}
}
