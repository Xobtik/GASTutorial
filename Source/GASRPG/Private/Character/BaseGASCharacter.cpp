// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseGASCharacter.h"

// Sets default values
ABaseGASCharacter::ABaseGASCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ABaseGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


