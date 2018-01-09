// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NotCatanGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ANotCatanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANotCatanGameMode();
	void startGame();
	void startTurn();
	void endTurn();
	TArray<uint8> roll() const;

private: 
	TArray<int32> m_playerIds;
};
