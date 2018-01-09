// Fill out your copyright notice in the Description page of Project Settings.

#include "Intersection.h"
#include "Engine/World.h"
#include "NotCatanGameState.h"

// Sets default values
AIntersection::AIntersection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AIntersection::initialize(const FMapIndex& mapIndex)
{
	m_mapIndex = mapIndex;
}

FMapIndex AIntersection::getMapIndex() const
{
	return m_mapIndex;
}

bool AIntersection::isValidBuildLocation(int playerId) const
{
	if (nullptr != m_structure)
	{
		return false;
	}
	TArray<AIntersection*> adjacentIntersections = GetWorld()->GetGameState<ANotCatanGameState>()->getTileMap()->getAdjecentIntersections(this);
	for (AIntersection* adjacentIntersection : adjacentIntersections)
	{
		if (nullptr != adjacentIntersection->getStructure())
		{
			return false;
		}
	}
	return true;
}

const AIntersectionStructure* AIntersection::getStructure() const
{
	return m_structure;
}

void AIntersection::setStructure(AIntersectionStructure* structure)
{
	m_structure = structure;
}
