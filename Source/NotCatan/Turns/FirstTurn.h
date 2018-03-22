#pragma once
#include "Turn.h"
#include "FirstTurn.generated.h"

UCLASS()
class NOTCATAN_API UFirstTurn : public UTurn
{
	GENERATED_BODY()

public:
	virtual ~UFirstTurn();
	UFUNCTION()
	virtual void startRound(ANotCatanGameMode* gameMode) override;

private:
	UFUNCTION()
	void promptPlaceSettlement();
	UFUNCTION()
	void promptPlaceRoad();
	UFUNCTION()
	void settlementPlaced();
	UFUNCTION()
	void roadPlaced();
	
	int32 m_currentPlayerIndex;
	bool m_wereFirstSettlementsPlaced;
};

