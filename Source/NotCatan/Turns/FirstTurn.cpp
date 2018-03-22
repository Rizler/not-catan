#include "FirstTurn.h"
#include "Actions/BuildSettlementAction.h"
#include "Engine/World.h"
#include "NotCatanGameMode.h"
#include "NotCatanGameState.h"


UFirstTurn::~UFirstTurn()
{
}

void UFirstTurn::startRound(ANotCatanGameMode* gameMode)
{
	Super::startRound(gameMode);

	promptPlaceSettlement();
}

void UFirstTurn::promptPlaceSettlement()
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = m_gameMode->getPlayers()[m_currentPlayerIndex];
	ABuildSettlementAction* buildAction = m_gameMode->GetWorld()->SpawnActor<ABuildSettlementAction>(ABuildSettlementAction::StaticClass(), spawnParams);
	ATileMap* tileMap = m_gameMode->GetGameState<ANotCatanGameState>()->getTileMap();
	buildAction->setValidBuildLocations(tileMap->getAvailableSettelemntBuildLocations(m_gameMode->getPlayers()[m_currentPlayerIndex], false));
	buildAction->actionPreformedEvent.AddDynamic(this, &UFirstTurn::settlementPlaced);
	buildAction->client_performAction();
}

void UFirstTurn::promptPlaceRoad()
{
	//m_gameMode->getPlayers()[m_currentPlayerIndex]->promptBuildRoad();
	roadPlaced();
}

void UFirstTurn::settlementPlaced()
{
	
	if (m_wereFirstSettlementsPlaced)
	{
		//yield resources
	}

	promptPlaceRoad();
}

void UFirstTurn::roadPlaced()
{
	if (!m_wereFirstSettlementsPlaced && m_currentPlayerIndex == m_gameMode->getPlayers().Num() - 1)
	{
		m_wereFirstSettlementsPlaced = true;
		m_currentPlayerIndex++;
	}

	if (m_wereFirstSettlementsPlaced)
	{
		m_currentPlayerIndex--;
		if (-1 == m_currentPlayerIndex)
		{
			endRound();
			return;
		}
	}
	else
	{
		m_currentPlayerIndex++;
	}

	promptPlaceSettlement();
}
