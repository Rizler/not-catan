// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGenerator.h"
#include "Engine/World.h"
#include "Engine/Blueprint.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "MapIndex.h"
#include "TileMap.h"
#include "TwoDArray.h"
#include "NotCatanGameState.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; 
}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

	generateMap();
	randomiseResources();
}

TArray<EResource> AMapGenerator::getResources()
{
	TArray<EResource> resources;
	resources.Add(EResource::DESERT);
	resources.Add(EResource::LUMBER);
	resources.Add(EResource::LUMBER);
	resources.Add(EResource::LUMBER);
	resources.Add(EResource::LUMBER);
	resources.Add(EResource::WOOL);
	resources.Add(EResource::WOOL);
	resources.Add(EResource::WOOL);
	resources.Add(EResource::WOOL);
	resources.Add(EResource::GRAIN);
	resources.Add(EResource::GRAIN);
	resources.Add(EResource::GRAIN);
	resources.Add(EResource::GRAIN);
	resources.Add(EResource::BRICK);
	resources.Add(EResource::BRICK);
	resources.Add(EResource::BRICK);
	resources.Add(EResource::ORE);
	resources.Add(EResource::ORE);
	resources.Add(EResource::ORE);
	return resources;
}

void AMapGenerator::calculateTileProperties()
{
	FBox tileBounds = getTileBounds();
	/*
	h = sin( 30?) * s
	r = cos( 30?) * s
	b = s + 2 * h
	a = 2 * r
	a: 173.205078, b: 200.000000, r: 86.602539, s: 100.000000, h: 50.000000
	*/
	m_tileA = tileBounds.GetExtent().X * 2;
	m_tileB = tileBounds.GetExtent().Y * 2;
	m_tileR = m_tileA / 2;
	m_tileS = m_tileR / FMath::Cos(FMath::DegreesToRadians(30));
	m_tileH = FMath::Sin(FMath::DegreesToRadians(30)) * m_tileS;

	m_mapTopLeftPosition = GetActorLocation();
	// Surrounding box center x
	//m_mapTopLeftPosition.X -= (MAP_SIZE * m_tileA + m_tileR) / 2 + m_tileR;
	// Center hex center position is x=0 with odd number size map
	m_mapTopLeftPosition.X -= (MAP_SIZE * m_tileA) / 2;
	m_mapTopLeftPosition.Y -= (MAP_SIZE * (m_tileH + m_tileS) + m_tileH) / 2 - m_tileS / 2 - m_tileH;
}

void AMapGenerator::generateMap()
{
	calculateTileProperties();

	m_tiles.resize(MAP_SIZE, MAP_SIZE);
	UWorld* world = GetWorld();
	for (int rowIndex = 0; rowIndex < MAP_SIZE; rowIndex++)
	{
		for (int colIndex = 0; colIndex < MAP_SIZE; colIndex++)
		{
			if (ETileType::NONE == MAP_TEMPLATE[rowIndex][colIndex])
			{
				continue;
			}

			FVector tilePosition = m_mapTopLeftPosition;
			tilePosition.Y += (m_tileH + m_tileS) * rowIndex;
			if (0 != rowIndex % 2)
			{
				tilePosition.X += m_tileR;
			}
			tilePosition.X += 2 * m_tileR * colIndex;

			ATile* tile = world->SpawnActor<ATile>(m_tile, tilePosition, FRotator::ZeroRotator);
			#if WITH_EDITOR
			tile->SetFolderPath("Map/Tiles");
			#endif 
			tile->initialize(FMapIndex(rowIndex, colIndex), MAP_TEMPLATE[rowIndex][colIndex], 0);
			m_tiles[rowIndex][colIndex] = tile;
		}
	}

	//TTwoDArray<AIntersection*> intersections = generateIntersections(m_tiles);
	TTwoDArray<AIntersection*> intersections;
	ATileMap* tileMap = world->SpawnActor<ATileMap>(ATileMap::StaticClass());
	tileMap->initialize(m_tiles, intersections);
	world->GetGameState<ANotCatanGameState>()->setTileMap(tileMap);
}

void AMapGenerator::randomiseResources()
{
	TArray<EResource> resources = getResources();
	for (int rowIndex = 0; rowIndex < MAP_SIZE; rowIndex++)
	{
		for (int colIndex = 0; colIndex < MAP_SIZE; colIndex++)
		{
			ATile* tile = m_tiles[rowIndex][colIndex];
			if (nullptr == tile)
			{
				continue;
			}

			if (ETileType::RESOURCE == MAP_TEMPLATE[rowIndex][colIndex])
			{
				int resourceIndex = FMath::RandRange(0, resources.Num() - 1);
				tile->setResource(resources[resourceIndex]);
				resources.RemoveAt(resourceIndex);
			}
		}
	}
}

TTwoDArray<AIntersection*> AMapGenerator::generateIntersections(const TTwoDArray<ATile*>& tiles)
{
	TTwoDArray<AIntersection*> intersections(tiles.getRowLength() + 1, tiles.getColumLength() * 2 + 2);
	FVector intersectionStartPosition = m_mapTopLeftPosition;
	intersectionStartPosition.X -= m_tileR;
	intersectionStartPosition.Y -= m_tileS / 2;

	for (int rowIndex = 0; rowIndex < MAP_SIZE; rowIndex++)
	{
		for (int colIndex = 0; colIndex < MAP_SIZE; colIndex++)
		{
			if (ETileType::RESOURCE != MAP_TEMPLATE[rowIndex][colIndex])
			{
				continue;
			}

			TArray<FMapIndex> intersectionIndices = ATileMap::getIntersectionOfTile(rowIndex, colIndex);
			for (const FMapIndex& intersectionIndex : intersectionIndices)
			{
				if (nullptr != intersections[intersectionIndex.row][intersectionIndex.col])
				{
					continue;
				}
				
				FVector intersectionPosition = intersectionStartPosition;
				intersectionPosition.X += intersectionIndex.col * m_tileR;
				intersectionPosition.Y += intersectionIndex.row * (m_tileS + m_tileH);
				if (intersectionIndex.col % 2 != intersectionIndex.row % 2)
				{
					intersectionPosition.Y -= m_tileH;
				}

				AIntersection* intersecion = GetWorld()->SpawnActor<AIntersection>(m_intersection, intersectionPosition, FRotator::ZeroRotator);
				#if WITH_EDITOR
				intersecion->SetFolderPath("Map/Intersections");
				#endif
				intersecion->initialize(FMapIndex(intersectionIndex.row, intersectionIndex.col));
				intersections[intersectionIndex.row][intersectionIndex.col] = intersecion;
			}
		}
	}
	return intersections;
}


FBox AMapGenerator::getTileBounds()
{
	AActor* tile = GetWorld()->SpawnActor<AActor>(m_tile, m_mapTopLeftPosition, FRotator::ZeroRotator);
	UStaticMeshComponent* tileMesh = Cast<UStaticMeshComponent>(tile->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	FBox boundingBox = tileMesh->Bounds.GetBox();
	tile->Destroy();
	return boundingBox;
}