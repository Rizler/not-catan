#include "Turn.h"
#include "NotCatanGameMode.h"
#include "Engine/World.h"

UTurn::~UTurn()
{
}

void UTurn::startRound(ANotCatanGameMode* gameMode)
{
	m_gameMode = gameMode;
}

void UTurn::endRound()
{
	m_gameMode->endTurnRound();
}
