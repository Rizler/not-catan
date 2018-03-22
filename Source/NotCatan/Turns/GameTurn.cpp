#include "GameTurn.h"
#include "NotCatanGameMode.h"

UGameTurn::~UGameTurn()
{

}

void UGameTurn::startRound(ANotCatanGameMode* gameMode)
{
	Super::startRound(gameMode);

	startNextTurn();
}

void UGameTurn::startNextTurn()
{
	ANotCatanPlayerController* currentPlayer = m_gameMode->getPlayers()[m_currentPlayerIndex];
	currentPlayer->playerEndedTurnEvent.AddDynamic(this, &UGameTurn::playerEndedTurn);
	m_gameMode->showNotification(FString::Printf(TEXT("%s's turn"), *currentPlayer->getPlayerState()->getName()));
	currentPlayer->client_startTurn();
}

void UGameTurn::playerEndedTurn()
{
	m_gameMode->getPlayers()[m_currentPlayerIndex]->playerEndedTurnEvent.RemoveDynamic(this, &UGameTurn::playerEndedTurn);
	m_currentPlayerIndex++;
	m_currentPlayerIndex %= m_gameMode->getPlayers().Num();
	startNextTurn();
}
