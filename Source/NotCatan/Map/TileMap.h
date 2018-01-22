// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "Intersection.h"
#include "TwoDArray.h"
#include "TileMap.generated.h"

UCLASS()
class NOTCATAN_API ATileMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileMap();
	void initialize(TTwoDArray<ATile*>&& tiles, TTwoDArray<AIntersection*>&& intersections);
	ATile* getTile(int32 row, int32 col) const;
	AIntersection* getIntersection(int32 row, int32 col) const;
	static TArray<FMapIndex> getIntersectionOfTile(int32 tileRow, int32 tileCol);
	TArray<AIntersection*> getIntersectionsOfTile(const ATile* tile) const;
	TArray<AIntersection*> getAdjecentIntersections(const AIntersection* intersection) const;
	TArray<ATile*> getTilesOfIntersection(const AIntersection* intersection) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TTwoDArray<ATile*> m_tiles;
	TTwoDArray<AIntersection*> m_intersections;
};
