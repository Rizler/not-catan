// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NotCatanGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NOTCATAN_API UNotCatanGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(BlueprintPure)
	FString getPlayerName() const;
	UFUNCTION(BlueprintCallable)
	void setPlayerName(const FString& playerName);
	
private:
	UPROPERTY()
	FString m_playerName;
};

