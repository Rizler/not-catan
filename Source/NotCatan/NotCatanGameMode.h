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
	void startGame();
	void startTurn();
	void endTurn();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private: 
	TArray<int32> m_playerIds;
	TArray<FColor> m_availableColors = { FColor::Black, FColor::Blue, FColor::Red, FColor::Green };
};
