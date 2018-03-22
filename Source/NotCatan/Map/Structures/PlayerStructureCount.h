#pragma once
#include "CoreMinimal.h"
#include "PlayerStructureCount.generated.h"

USTRUCT()
struct NOTCATAN_API FPlayerStructureCount
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 roads = 15;
	UPROPERTY()
	int32 settlements = 5;
	UPROPERTY()
	int32 cities = 4;
};