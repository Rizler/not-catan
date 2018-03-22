// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "Intersection.h"
#include "Map/Structures/Road.h"
#include "TwoDArray.h"
#include "TileMap.generated.h"

UCLASS()
class NOTCATAN_API ATileMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileMap();
	void initialize(TTwoDArray<ATile*>& tiles, TTwoDArray<AIntersection*>& intersections);
	ATile* getTile(int32 row, int32 col) const;
	ATile* getTile(const FMapIndex& mapIndex) const;
	AIntersection* getIntersection(int32 row, int32 col) const;
	AIntersection* getIntersection(const FMapIndex& mapIndex) const;
	static TArray<FMapIndex> getIntersectionOfTile(int32 tileRow, int32 tileCol);
	TArray<AIntersection*> getIntersectionsOfTile(const ATile* tile) const;
	TArray<AIntersection*> getAdjecentIntersections(const AIntersection* intersection) const;
	TArray<ATile*> getTilesOfIntersection(const AIntersection* intersection) const;
	TArray<ARoad*> getConnectedRoads(const AIntersection* intersection) const;
	
	TArray<FRoadLocation> getAvailableRoadBuildLocations(const ANotCatanPlayerController* player) const;
	TArray<FMapIndex> getAvailableSettelemntBuildLocations(const ANotCatanPlayerController* player, bool isRoadRequired) const;
	TArray<FMapIndex> getAvailableCityBuildLocations(const ANotCatanPlayerController* player) const;

	void highlightRoads(const TArray<FRoadLocation>& roadLocations);
	void disableHighlightedRoads();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION(NetMulticast, Reliable)
	void multicast_netInit();
	
private:
	bool isValidRoadLocation();
	bool isPlayerRoadConnectedToIntersection(const AIntersection* intersection, const ANotCatanPlayerController* player) const;

	TTwoDArray<ATile*> m_tiles;
	TTwoDArray<AIntersection*> m_intersections;
	UPROPERTY(Replicated)
	TArray<ARoad*> m_roads;
};
