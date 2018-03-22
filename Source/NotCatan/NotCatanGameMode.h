// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UniquePtr.h"
#include "GameFramework/GameModeBase.h"
#include "NotCatanPlayerController.h"
#include "Turns/Turn.h"
#include "NotCatanGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ANotCatanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void startGame();
	void startTurn();
	void endTurnRound();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	TArray<ANotCatanPlayerController*> getPlayers() const;
	void setPlayers(const TArray<ANotCatanPlayerController*>& players);
	void showNotification(const FString& message);

private: 
	int32 m_currentTurnType;
	UPROPERTY()
	UTurn* m_currentTurn;
	TArray<ANotCatanPlayerController*> m_players;
	TArray<FColor> m_availableColors = { FColor::Black, FColor::Blue, FColor::Red, FColor::Green };
};