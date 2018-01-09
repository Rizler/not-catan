// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NotCatanGameMode.h"
#include "NotCatanPlayerController.h"
#include "NotCatanPawn.h"
#include "NotCatanGameState.h"
#include "NotCatanPlayerState.h"

ANotCatanGameMode::ANotCatanGameMode()
{
	GameStateClass = ANotCatanGameState::StaticClass();
	PlayerStateClass = ANotCatanPlayerState::StaticClass();
	DefaultPawnClass = ANotCatanPawn::StaticClass();
	PlayerControllerClass = ANotCatanPlayerController::StaticClass();
}

void ANotCatanGameMode::startGame()
{
	for (APlayerState* player : GameState->PlayerArray)
	{
		m_playerIds.Add(player->PlayerId);
	}
}

void ANotCatanGameMode::endTurn()
{

}

TArray<uint8> ANotCatanGameMode::roll() const
{
	TArray<uint8> result;
	result.Add(FMath::RandRange(1, 6));
	result.Add(FMath::RandRange(1, 6));
	return result;
}