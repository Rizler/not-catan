// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Map/TileMap.h"
#include "NotCatanGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStateChanged);

/**
 * 
 */
UCLASS()
class NOTCATAN_API ANotCatanGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ATileMap* getTileMap() const;
	void setTileMap(ATileMap* tileMap);

	UPROPERTY(BlueprintAssignable)
	FGameStateChanged m_gameStateChanged;
	
private:
	UPROPERTY()
	ATileMap* m_tileMap;


};