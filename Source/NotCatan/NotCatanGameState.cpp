// Fill out your copyright notice in the Description page of Project Settings.

#include "NotCatanGameState.h"
#include "Net/UnrealNetwork.h"

ATileMap* ANotCatanGameState::getTileMap() const
{
	return m_tileMap;
}

void ANotCatanGameState::setTileMap(ATileMap* tileMap)
{
	m_tileMap = tileMap;
}

void ANotCatanGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANotCatanGameState, m_tileMap);
}
