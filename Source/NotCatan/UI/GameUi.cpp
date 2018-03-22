// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUi.h"

UPlayersDisplay* UGameUi::getPlayersDisplay() const
{
	return m_playersDisplay;
}

void UGameUi::enableGameUi_Implementation()
{}

void UGameUi::enableActionsUi_Implementation(bool shouldEnable)
{}

void UGameUi::enableRollButton_Implementation()
{}
