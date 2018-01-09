// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TileMap.h"
#include "NotCatanGameState.generated.h"

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
	
private:
	UPROPERTY()
	ATileMap* m_tileMap;


};