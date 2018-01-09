// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapIndex.h"
#include "IntersectionStructure.h"
#include "Intersection.generated.h"

UCLASS()
class NOTCATAN_API AIntersection : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIntersection();
	void initialize(const FMapIndex& mapIndex);
	FMapIndex getMapIndex() const;
	bool isValidBuildLocation(int playerId) const;
	const AIntersectionStructure* getStructure() const;
	void setStructure(AIntersectionStructure* structure);

private:
	FMapIndex m_mapIndex;
	AIntersectionStructure* m_structure;
};
