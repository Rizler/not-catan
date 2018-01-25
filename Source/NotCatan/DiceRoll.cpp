#include "DiceRoll.h"

FDiceRoll::FDiceRoll()
{
	roll();
}

void FDiceRoll::roll()
{
	die1 = FMath::RandRange(1, 6);
	die2 = FMath::RandRange(1, 6);
	sum = die1 + die2;
}
