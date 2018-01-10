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

void ANotCatanGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Post Login!"));
	ANotCatanPlayerController* playerController = Cast<ANotCatanPlayerController>(NewPlayer);
	playerController->client_setName();
	playerController->getPlayerState()->setColor(m_availableColors.Pop());
}

void ANotCatanGameMode::Logout(AController* Existing)
{
	m_availableColors.Add(Cast<ANotCatanPlayerController>(Existing)->getPlayerState()->getColor());
}
