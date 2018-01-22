// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotCatanPlayerState.h"
#include "PlayersDisplay.generated.h"

/**
 * 
 */
UCLASS()
class NOTCATAN_API UPlayersDisplay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void addPlayerInfo(const ANotCatanPlayerState* playerState);
};
