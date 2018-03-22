#pragma once
#include "Turn.h"
#include "GameTurn.generated.h"

UCLASS()
class NOTCATAN_API UGameTurn : public UTurn
{
	GENERATED_BODY()

public:
	virtual ~UGameTurn();
	UFUNCTION()
	virtual void startRound(ANotCatanGameMode* gameMode) override;

private:
	void startNextTurn();
	UFUNCTION()
	void playerEndedTurn();

	int32 m_currentPlayerIndex;
};

