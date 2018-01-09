// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NotCatanPlayerState.generated.h"

/**
 *
 */
UCLASS()
class NOTCATAN_API ANotCatanPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION()
	uint8 getVictoryPoints() const;
	UFUNCTION()
	void setVictoryPoints(uint8 victoryPoints);
	UFUNCTION()
	uint8 getResourcesCount() const;
	UFUNCTION()
	uint8 getDevelopmentCardsCount();
	UFUNCTION()
	FColor getColor() const;
	
private:
	UPROPERTY()
	uint8 m_victoryPoints;
	UPROPERTY()
	uint8 m_resourcesCount;
	UPROPERTY()
	uint8 m_developmentCardsCount;
	UPROPERTY()
	FColor m_color;
};
