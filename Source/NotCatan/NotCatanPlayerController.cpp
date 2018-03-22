// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NotCatanPlayerController.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Engine.h"
#include "NotCatanPawn.h"
#include "NotCatanGameInstance.h"
#include "NotCatanGameState.h"
#include "NotCatanGameMode.h"
#include "DiceRoll.h"

ANotCatanPlayerController::ANotCatanPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	
	static ConstructorHelpers::FClassFinder<UGameUi> gameUiAsset(TEXT("/Game/NotCatan/UI/UI_Game"));
	m_gameUiClass = gameUiAsset.Class;
}

void ANotCatanPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		m_gameUi = CreateWidget<UGameUi>(this, m_gameUiClass);
		m_gameUi->AddToViewport();
	}
}

ANotCatanPlayerState* ANotCatanPlayerController::getPlayerState() const
{
	return Cast<ANotCatanPlayerState>(PlayerState);
}

UPlayersDisplay* ANotCatanPlayerController::getPlayersDisplay() const
{
	return m_gameUi->getPlayersDisplay();
}

void ANotCatanPlayerController::setAction(AAction* action)
{
	Cast<ANotCatanPawn>(GetPawn())->setAction(action);
}

bool ANotCatanPlayerController::server_setName_Validate(const FString& name)
{
	return true;
}

void ANotCatanPlayerController::server_setName_Implementation(const FString& name)
{
	UE_LOG(LogTemp, Warning, TEXT("server_setName_Implementation"));
	getPlayerState()->setName(name);
}

bool ANotCatanPlayerController::server_rollDice_Validate()
{
	return true;
}

void ANotCatanPlayerController::server_rollDice_Implementation()
{
	FDiceRoll roll;
	playerRolledEvent.Broadcast(this, roll);
	GetWorld()->GetAuthGameMode<ANotCatanGameMode>()->showNotification(FString::Printf(TEXT("%s rolled %d, %d"), *getPlayerState()->getName(), roll.die1, roll.die2));
}

bool ANotCatanPlayerController::server_endTurn_Validate()
{
	return true;
}

void ANotCatanPlayerController::server_endTurn_Implementation()
{
	playerEndedTurnEvent.Broadcast();
}

void ANotCatanPlayerController::client_promptRoll_Implementation()
{
	m_gameUi->enableRollButton();
}

void ANotCatanPlayerController::client_startTurn_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, "Your Turn!");
	m_gameUi->enableActionsUi(true);
}

void ANotCatanPlayerController::client_startGame_Implementation()
{
	m_gameUi->enableGameUi();
}

void ANotCatanPlayerController::client_setName_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("client_setName_Implementation playername in gameinstance: %s"), *(Cast<UNotCatanGameInstance>(GetWorld()->GetGameInstance())->getPlayerName()));
	server_setName(Cast<UNotCatanGameInstance>(GetWorld()->GetGameInstance())->getPlayerName());
}

void ANotCatanPlayerController::client_showNotification_Implementation(const FString& notification)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, notification);
}