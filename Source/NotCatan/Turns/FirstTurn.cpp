#include "FirstTurn.h"
#include "Actions/BuildSettlementAction.h"
#include "Actions/BuildRoadAction.h"
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
	buildAction->client_perform();
}

void UFirstTurn::promptPlaceRoad(const TArray<FRoadLocation>& validBuildLocations)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = m_gameMode->getPlayers()[m_currentPlayerIndex];
	ABuildRoadAction* buildAction = m_gameMode->GetWorld()->SpawnActor<ABuildRoadAction>(ABuildRoadAction::StaticClass(), spawnParams);

	ATileMap* tileMap = m_gameMode->GetGameState<ANotCatanGameState>()->getTileMap();
	buildAction->setValidBuildLocations(validBuildLocations);
	buildAction->actionPreformedEvent.AddDynamic(this, &UFirstTurn::roadPlaced);
	buildAction->client_perform();
}

void UFirstTurn::settlementPlaced(AAction* action)
{
	if (m_wereFirstSettlementsPlaced)
	{
		//TODO yield resources
	}
	ATileMap* tileMap = m_gameMode->GetGameState<ANotCatanGameState>()->getTileMap();
	ABuildSettlementAction* buildAction = Cast<ABuildSettlementAction>(action);
	promptPlaceRoad(tileMap->getConnectedRoadLocations(buildAction->getBuiltSettlementLocation()));
}

void UFirstTurn::roadPlaced(AAction* action)
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
