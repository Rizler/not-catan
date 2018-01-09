// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	NONE,
	RESOURCE,
	SEA,
};

UENUM(BlueprintType)
enum class EResource : uint8
{
	NONE,
	DESERT,
	GRAIN,
	WOOL,
	BRICK,
	ORE,
	LUMBER,
};
