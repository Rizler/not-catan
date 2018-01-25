#pragma once
#include "CoreMinimal.h"
#include "DiceRoll.generated.h"

USTRUCT()
struct NOTCATAN_API FDiceRoll
{
	GENERATED_BODY()

public:
	FDiceRoll();
	void roll();

	UPROPERTY()
	int32 die1;
	UPROPERTY()
	int32 die2;
	UPROPERTY()
	int32 sum;
};