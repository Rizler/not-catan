// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NotCatanPlayerState.h"
#include "Actions/Action.h"
#include "Map/MapIndex.h"
#include "Map/Structures/Road.h"
#include "UI/PlayersDisplay.h"
#include "UI/GameUi.h"
#include "DiceRoll.h"
#include "NotCatanPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerEndedTurn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerRolled, ANotCatanPlayerController*, playerController, FDiceRoll, rollResult);

UCLASS()
class ANotCatanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANotCatanPlayerController();

	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintPure)
	ANotCatanPlayerState* getPlayerState() const;
	UFUNCTION(BlueprintPure)
	UPlayersDisplay* getPlayersDisplay() const;
	UFUNCTION()
	void setAction(AAction* action);

	UFUNCTION(Server, Reliable, WithValidation)
	void server_setName(const FString& name);
	bool server_setName_Validate(const FString& name);
	void server_setName_Implementation(const FString& name);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void server_rollDice();
	bool server_rollDice_Validate();
	void server_rollDice_Implementation();
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void server_endTurn();
	bool server_endTurn_Validate();
	void server_endTurn_Implementation();

	UFUNCTION(Client, Reliable)
	void client_setName();
	
	UFUNCTION(Client, Reliable)
	void client_promptRoll();
	UFUNCTION(Client, Reliable)
	void client_startTurn();
	UFUNCTION(Client, Reliable)
	void client_startGame();
	UFUNCTION(Client, Reliable)
	void client_showNotification(const FString& notification);
	

protected: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameUi> m_gameUiClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameUi* m_gameUi;

public:
	FPlayerEndedTurn playerEndedTurnEvent;
	FPlayerRolled playerRolledEvent;
};


