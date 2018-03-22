// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NotCatanGameMode.h"
#include "Engine/World.h"
#include "NotCatanPlayerController.h"
#include "NotCatanPawn.h"
#include "NotCatanGameState.h"
#include "NotCatanPlayerState.h"
#include "Turns/FirstTurn.h"
#include "Turns/OrderPlayersTurn.h"
#include "Turns/GameTurn.h"

void ANotCatanGameMode::startGame()
{
	GetGameState<ANotCatanGameState>()->getTileMap()->multicast_netInit();
	for (FConstPlayerControllerIterator controllerIterator = GetWorld()->GetPlayerControllerIterator(); controllerIterator; ++controllerIterator)
	{
		ANotCatanPlayerController* playerController = Cast<ANotCatanPlayerController>(*controllerIterator);
		playerController->client_startGame();
		m_players.Add(playerController);
	}
	m_currentTurn = NewObject<UOrderPlayersTurn>();
	m_currentTurn->startRound(this);
}

void ANotCatanGameMode::endTurnRound()
{
	switch (m_currentTurnType)
	{
	case 0:
		m_currentTurn = NewObject<UFirstTurn>();
		break;
	case 1:
		m_currentTurn = NewObject<UGameTurn>();
		break;
	}
	m_currentTurnType++;
	m_currentTurn->startRound(this);
}

void ANotCatanGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ANotCatanPlayerController* playerController = Cast<ANotCatanPlayerController>(NewPlayer);
	playerController->client_setName();
	playerController->getPlayerState()->setColor(m_availableColors.Pop());
}

void ANotCatanGameMode::Logout(AController* Existing)
{
	Super::Logout(Existing);

	m_availableColors.Add(Cast<ANotCatanPlayerController>(Existing)->getPlayerState()->getColor());
}

TArray<ANotCatanPlayerController*> ANotCatanGameMode::getPlayers() const
{
	return m_players;
}

void ANotCatanGameMode::setPlayers(const TArray<ANotCatanPlayerController*>& players)
{
	m_players = players;
}

void ANotCatanGameMode::showNotification(const FString& message)
{
	for (ANotCatanPlayerController* player : m_players)
	{
		player->client_showNotification(message);
	}
}