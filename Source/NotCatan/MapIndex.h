// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapIndex.generated.h"

USTRUCT()
struct FMapIndex
{
	GENERATED_BODY()

public:
	FMapIndex();
	FMapIndex(int32 row, int32 col);
	bool operator==(const FMapIndex& other) const;

	UPROPERTY()
	int32 row;
	UPROPERTY()
	int32 col;
};
