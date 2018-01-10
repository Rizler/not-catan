// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NotCatanPlayerController.h"
#include "NotCatanGameInstance.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"

ANotCatanPlayerController::ANotCatanPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

ANotCatanPlayerState * ANotCatanPlayerController::getPlayerState() const
{
	return Cast<ANotCatanPlayerState>(PlayerState);
}

bool ANotCatanPlayerController::server_setName_Validate(const FString& name)
{
	return true;
}

void ANotCatanPlayerController::server_setName_Implementation(const FString& name)
{
	UE_LOG(LogTemp, Warning, TEXT("server_setName_Implementation"));
	getPlayerState()->setName(name);
}

void ANotCatanPlayerController::client_setName_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("client_setName_Implementation playername in gameinstance: %s"), *(Cast<UNotCatanGameInstance>(GetWorld()->GetGameInstance())->getPlayerName()));
	server_setName(Cast<UNotCatanGameInstance>(GetWorld()->GetGameInstance())->getPlayerName());
}
