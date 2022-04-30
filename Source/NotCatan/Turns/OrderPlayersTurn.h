#pragma once
#include "CoreMinimal.h"
#include "Turn.h"
#include "DiceRoll.h"
#include "NotCatan/NotCatanGameMode.h"
#include "OrderPlayersTurn.generated.h"

UCLASS()
class NOTCATAN_API UOrderPlayersTurn : public UTurn
{
	GENERATED_BODY()

public:
	virtual ~UOrderPlayersTurn();
	virtual void startRound(ANotCatanGameMode* gameMode) override;
	virtual void playerRolled(ANotCatanPlayerController* playerController, FDiceRoll rollResult);

private:
	void sortPlayers();
	void promptRoll();

	struct FPlayerTurnOrder
	{
		FPlayerTurnOrder(ANotCatanPlayerController* playerController);
		bool operator<(const FPlayerTurnOrder& other) const;

		ANotCatanPlayerController* playerController;
		int32 rollResult;
		int32 turnOrder;
	};

	TArray<ANotCatanPlayerController*> m_orderedPlayers;
	TArray<FPlayerTurnOrder> m_playersToSort;
	int32 m_rollingPlayerIndex;
	int32 m_turnNumberSlot;
};

