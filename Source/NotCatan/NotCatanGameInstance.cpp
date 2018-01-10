// Fill out your copyright notice in the Description page of Project Settings.

#include "NotCatanGameInstance.h"

FString UNotCatanGameInstance::getPlayerName() const
{
	return m_playerName;
}

void UNotCatanGameInstance::setPlayerName(const FString& playerName)
{
	m_playerName = playerName;
}



