#pragma once

#include "CoreMinimal.h"
#include "NotCatanPlayerController.h"
#include "Turn.generated.h"

class ANotCatanGameMode;

UCLASS()
class NOTCATAN_API UTurn : public UObject
{
	GENERATED_BODY()

public:
	virtual ~UTurn();
	UFUNCTION()
	virtual void startRound(ANotCatanGameMode* gameMode);
	UFUNCTION()
	virtual void endRound();

protected:
	ANotCatanGameMode* m_gameMode;
};

