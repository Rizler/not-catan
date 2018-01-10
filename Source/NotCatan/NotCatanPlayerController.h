// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NotCatanPlayerState.h"
#include "NotCatanPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class ANotCatanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANotCatanPlayerController();

	ANotCatanPlayerState* getPlayerState() const;

	UFUNCTION(Server, Reliable, WithValidation)
	void server_setName(const FString& name);
	bool server_setName_Validate(const FString& name);
	void server_setName_Implementation(const FString& name);

	UFUNCTION(Client, Reliable)
	void client_setName();
};


