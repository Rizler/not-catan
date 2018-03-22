// Fill out your copyright notice in the Description page of Project Settings.

#include "TileMap.h"
#include "Public/EngineUtils.h"
#include "Net/UnrealNetwork.h"
#include "Map/MapGenerator.h"


// Sets default values
ATileMap::ATileMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bAlwaysRelevant = true;
}

void ATileMap::initialize(TTwoDArray<ATile*>& tiles, TTwoDArray<AIntersection*>& intersections)
{
	m_tiles = tiles;
	m_intersections = intersections;
}

ATile* ATileMap::getTile(int32 row, int32 col) const
{
	if (!m_tiles.isInBounds(row, col))
	{
		return nullptr;
	}
	return m_tiles[row][col];
}

ATile* ATileMap::getTile(const FMapIndex& mapIndex) const
{
	return getTile(mapIndex.row, mapIndex.col);
}

AIntersection* ATileMap::getIntersection(int32 row, int32 col) const
{
	if (!m_intersections.isInBounds(row, col))
	{
		return nullptr;
	}
	return m_intersections[row][col];
}

AIntersection* ATileMap::getIntersection(const FMapIndex& mapIndex) const
{
	return getIntersection(mapIndex.row, mapIndex.col);
}

TArray<FMapIndex> ATileMap::getIntersectionOfTile(int32 tileRow, int32 tileCol)
{
	int32 leftIntersectionsCol = tileCol * 2 + tileRow % 2;
	int32 midIntersectionsCol = leftIntersectionsCol + 1;
	int32 rightIntersectionsCol = leftIntersectionsCol + 2;
	TArray<FMapIndex> intersectionIndices;
	// Top left
	intersectionIndices.Add(FMapIndex(tileRow, leftIntersectionsCol));
	// Top									
	intersectionIndices.Add(FMapIndex(tileRow, midIntersectionsCol));
	// Top Right							
	intersectionIndices.Add(FMapIndex(tileRow, rightIntersectionsCol));
	// Bottom left							
	intersectionIndices.Add(FMapIndex(tileRow + 1, leftIntersectionsCol));
	// Bottom								
	intersectionIndices.Add(FMapIndex(tileRow + 1, midIntersectionsCol));
	// Bottom right							
	intersectionIndices.Add(FMapIndex(tileRow + 1, rightIntersectionsCol));

	return intersectionIndices;
}

TArray<AIntersection*> ATileMap::getIntersectionsOfTile(const ATile* tile) const
{
	TArray<FMapIndex> intersectionIndices = getIntersectionOfTile(tile->getMapIndex().row, tile->getMapIndex().col);
	TArray<AIntersection*> intersections;
	for (const FMapIndex& intersectionIndex : intersectionIndices)
	{
		intersections.Add(getIntersection(intersectionIndex.row, intersectionIndex.col));
	}
	return intersections;
}

TArray<AIntersection*> ATileMap::getAdjecentIntersections(const AIntersection* intersection) const
{
	TArray<AIntersection*> adjacentIntersections;
	FMapIndex intersectionIndex = intersection->getMapIndex();
	// Left
	adjacentIntersections.Add(getIntersection(intersectionIndex.row, intersectionIndex.col - 1));
	// Right
	adjacentIntersections.Add(getIntersection(intersectionIndex.row, intersectionIndex.col + 1));
	// Top / Bottom
	int adjacentRowOffset = (intersectionIndex.row % 2 == intersectionIndex.col % 2) ? 1 : -1;
	adjacentIntersections.Add(getIntersection(intersectionIndex.row + adjacentRowOffset, intersectionIndex.col));

	adjacentIntersections.Remove(nullptr);
	return adjacentIntersections;
}

TArray<ATile*> ATileMap::getTilesOfIntersection(const AIntersection* intersection) const
{
	FMapIndex intersectionIndex = intersection->getMapIndex();
	int32 midTileCol = intersectionIndex.col / 2 - (intersectionIndex.col + 1) % 2;
	int32 leftTileCol = intersectionIndex.col / 2 - 1;
	int32 rightTileCol = intersectionIndex.col / 2;
	int32 midTileRow = intersectionIndex.row;
	int32 leftRightTileRow = intersectionIndex.row;
	// Check if intersection is at the bottom of a tile
	if (intersectionIndex.row % 2 == intersectionIndex.col % 2)
	{
		midTileRow--;
	}
	else
	{
		leftRightTileRow--;
	}
	
	TArray<ATile*> tiles;
	tiles.Add(getTile(midTileRow, midTileCol));
	tiles.Add(getTile(leftRightTileRow, leftTileCol));
	tiles.Add(getTile(leftRightTileRow, rightTileCol));
	
	tiles.Remove(nullptr);
	return tiles;
}

TArray<ARoad*> ATileMap::getConnectedRoads(const AIntersection* intersection) const
{
	return TArray<ARoad*>();
}

TArray<FRoadLocation> ATileMap::getAvailableRoadBuildLocations(const ANotCatanPlayerController* player) const
{
	TSet<FRoadLocation> validLocations;

	return validLocations.Array();
}

TArray<FMapIndex> ATileMap::getAvailableSettelemntBuildLocations(const ANotCatanPlayerController* player, bool isRoadRequired) const
{
	TArray<FMapIndex> validLocations;
	for (int i = 0; i < m_intersections.getRowLength(); i++)
	{
		for (int j = 0; j < m_intersections.getColumnLength(); j++)
		{
			AIntersection* intersection = m_intersections[i][j];
			if (nullptr == intersection)
			{
				continue;
			}
			if (intersection->isValidBuildLocation(player->GetUniqueID()))
			{
				if (isRoadRequired)
				{
					if (isPlayerRoadConnectedToIntersection(intersection, player))
					{
						validLocations.Add(intersection->getMapIndex());
					}
				}
				else
				{
					validLocations.Add(intersection->getMapIndex());
				}
			}
		}
	}
	return validLocations;
}

TArray<FMapIndex> ATileMap::getAvailableCityBuildLocations(const ANotCatanPlayerController* player) const
{
	TArray<FMapIndex> validLocations;
	for (int i = 0; i < m_intersections.getRowLength(); i++)
	{
		for (int j = 0; j < m_intersections.getRowLength(); j++)
		{
			AIntersection* intersection = m_intersections[i][j];
			if (nullptr != intersection->getStructure() && intersection->getStructure()->GetOwner()->GetUniqueID() == player->GetUniqueID())
			{
				if (intersection->getStructure()->isSettlement())
				{
					validLocations.Add(intersection->getMapIndex());
				}
			}
		}
	}
	return validLocations;
}

void ATileMap::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATileMap, m_roads);
}

void ATileMap::multicast_netInit_Implementation()
{
	m_tiles.resize(AMapGenerator::MAP_SIZE, AMapGenerator::MAP_SIZE);
	for (TActorIterator<ATile> actorIterator(GetWorld()); actorIterator; ++actorIterator)
	{
		ATile* tile = *actorIterator;
		m_tiles[tile->getMapIndex().row][tile->getMapIndex().col] = tile;
	}

	m_intersections.resize(m_tiles.getRowLength() + 1, m_tiles.getColumnLength() * 2 + 2);
	for (TActorIterator<AIntersection> actorIterator(GetWorld()); actorIterator; ++actorIterator)
	{
		AIntersection* intersection = *actorIterator;
		m_intersections[intersection->getMapIndex().row][intersection->getMapIndex().col] = intersection;
	}
}

bool ATileMap::isPlayerRoadConnectedToIntersection(const AIntersection* intersection, const ANotCatanPlayerController* player) const
{
	for (ARoad* road : m_roads)
	{
		if (road->getOwner()->GetUniqueID() == player->GetUniqueID() && road->isOnIntersection(intersection->getMapIndex()))
		{
			return true;
		}
	}
	return false;
}
