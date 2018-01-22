// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayersDisplay.h"
#include "GameUi.generated.h"

/**
 * 
 */
UCLASS()
class NOTCATAN_API UGameUi : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	UPlayersDisplay* getPlayersDisplay() const;

protected:
	UPROPERTY(BlueprintReadWrite)
	UPlayersDisplay* m_playersDisplay;
};