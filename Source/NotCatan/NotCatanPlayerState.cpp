// Fill out your copyright notice in the Description page of Project Settings.

#include "NotCatanPlayerState.h"
#include "NotCatanGameInstance.h"
#include "Net/UnrealNetwork.h"


FString ANotCatanPlayerState::getName() const
{
	return m_name;
}

void ANotCatanPlayerState::setName(const FString & name)
{
	m_name = name;
	updateUi();
}

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

uint8 ANotCatanPlayerState::getDevelopmentCardsCount() const
{
	return m_developmentCardsCount;
}

FColor ANotCatanPlayerState::getColor() const
{
	return m_color;
}

void ANotCatanPlayerState::setColor(const FColor & color)
{
	m_color = color;
	updateUi();
}

void ANotCatanPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANotCatanPlayerState, m_name);
	DOREPLIFETIME(ANotCatanPlayerState, m_victoryPoints);
	DOREPLIFETIME(ANotCatanPlayerState, m_resourcesCount);
	DOREPLIFETIME(ANotCatanPlayerState, m_developmentCardsCount);
	DOREPLIFETIME(ANotCatanPlayerState, m_color);
}

void ANotCatanPlayerState::onRep_victoryPoints()
{
	UE_LOG(LogTemp, Warning, TEXT("Replicated victory points: %d"), m_victoryPoints);
}

void ANotCatanPlayerState::onRep_color()
{
	UE_LOG(LogTemp, Warning, TEXT("Replicated color: %d"), m_color.DWColor());
	updateUi();
}

void ANotCatanPlayerState::onRep_name()
{
	UE_LOG(LogTemp, Warning, TEXT("Replicated name: %s"), *m_name);
	updateUi();
}

void ANotCatanPlayerState::updateUi_Implementation()
{

}
