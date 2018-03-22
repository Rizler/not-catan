#include "OrderPlayersTurn.h"
#include "NotCatanGameState.h"


UOrderPlayersTurn::~UOrderPlayersTurn()
{
}

void UOrderPlayersTurn::startRound(ANotCatanGameMode* gameMode)
{
	Super::startRound(gameMode);

	for (ANotCatanPlayerController* player : m_gameMode->getPlayers())
	{
		m_playersToSort.Add(FPlayerTurnOrder(player));
	}

	promptRoll();
}

void UOrderPlayersTurn::playerRolled(ANotCatanPlayerController* playerController, FDiceRoll rollResult)
{
	playerController->playerRolledEvent.RemoveDynamic(this, &UOrderPlayersTurn::playerRolled);

	m_playersToSort[m_rollingPlayerIndex].rollResult = rollResult.sum;
	m_rollingPlayerIndex++;
	if (m_rollingPlayerIndex == m_playersToSort.Num())
	{
		sortPlayers();
		m_rollingPlayerIndex = 0;
	}
	else
	{
		promptRoll();
	}
}

void UOrderPlayersTurn::promptRoll()
{
	m_playersToSort[m_rollingPlayerIndex].playerController->playerRolledEvent.AddDynamic(this, &UOrderPlayersTurn::playerRolled);

	m_playersToSort[m_rollingPlayerIndex].playerController->client_promptRoll();
}

void UOrderPlayersTurn::sortPlayers()
{
	m_playersToSort.Sort();
	int32 turn = m_playersToSort[0].turnOrder;
	for (int32 i = 0; i < m_playersToSort.Num(); i++)
	{
		bool shouldReroll = false;
		m_playersToSort[i].turnOrder = turn;
		for (int j = i + 1; j < m_playersToSort.Num(); j++)
		{
			if (m_playersToSort[j].rollResult == m_playersToSort[i].rollResult)
			{
				m_playersToSort[j].turnOrder = m_playersToSort[i].turnOrder;
				i++;
				turn++;
				shouldReroll = true;
			}
			else
			{
				break;
			}
		}

		if (!shouldReroll)
		{
			m_orderedPlayers.Add(m_playersToSort[i].playerController);
			m_playersToSort.RemoveAt(i);
			i--;
		}
		turn++;
	}

	if (0 != m_playersToSort.Num())
	{
		promptRoll();
	}
	else 
	{
		m_gameMode->setPlayers(m_orderedPlayers);
		endRound();
	}
}


// ********************** FPlayerTurnOrder **********************
UOrderPlayersTurn::FPlayerTurnOrder::FPlayerTurnOrder(ANotCatanPlayerController* playerController) :
	playerController(playerController), rollResult(0), turnOrder(0)
{}

bool UOrderPlayersTurn::FPlayerTurnOrder::operator<(const FPlayerTurnOrder& other) const
{
	if (this->turnOrder != other.turnOrder)
	{
		return this->turnOrder > other.turnOrder;
	}
	return this->rollResult > other.rollResult;
}
