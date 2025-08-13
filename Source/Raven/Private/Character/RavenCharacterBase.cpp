// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RavenCharacterBase.h"

// Sets default values
ARavenCharacterBase::ARavenCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARavenCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARavenCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARavenCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

