// Fill out your copyright notice in the Description page of Project Settings.

#include "NotCatanPlayerState.h"

uint8 ANotCatanPlayerState::getVictoryPoints() const
{
	return m_victoryPoints;
}

void ANotCatanPlayerState::setVictoryPoints(uint8 victoryPoints)
{
	m_victoryPoints = victoryPoints;
}

uint8 ANotCatanPlayerState::getResourcesCount() const
{
	return m_resourcesCount;
}

uint8 ANotCatanPlayerState::getDevelopmentCardsCount()
{
	return m_developmentCardsCount;
}

FColor ANotCatanPlayerState::getColor() const
{
	return m_color;
}
