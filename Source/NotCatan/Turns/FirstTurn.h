#pragma once
#include "Turn.h"
#include "Map/Structures/Road.h"
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
	void promptPlaceRoad(const TArray<FRoadLocation>& validBuildLocations);
	UFUNCTION()
	void settlementPlaced(AAction* action);
	UFUNCTION()
	void roadPlaced(AAction* action);
	
	int32 m_currentPlayerIndex;
	bool m_wereFirstSettlementsPlaced;
};

