// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGenerator.h"
#include "Engine/World.h"
#include "Engine/Blueprint.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "MapIndex.h"
#include "TileMap.h"
#include "Intersection.h"
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

void AMapGenerator::generateMap()
{
	FBox tileBounds = getTileBounds();
	/*
	h = sin( 30?) * s
	r = cos( 30?) * s
	b = s + 2 * h
	a = 2 * r
	a: 173.205078, b: 200.000000, r: 86.602539, s: 100.000000, h: 50.000000
	*/
	float a = tileBounds.GetExtent().X * 2;
	float b = tileBounds.GetExtent().Y * 2;
	float r = a / 2;
	float s = r / FMath::Cos(FMath::DegreesToRadians(30));
	float h = FMath::Sin(FMath::DegreesToRadians(30)) * s;

	TArray<EResource> resources = getResources();
	TTwoDArray<ATile*> tiles(MAP_SIZE, MAP_SIZE);
	UWorld* world = GetWorld();
	for (int rowIndex = 0; rowIndex < MAP_SIZE; rowIndex++)
	{
		for (int colIndex = 0; colIndex < MAP_SIZE; colIndex++)
		{
			if (ETileType::NONE == MAP_TEMPLATE[rowIndex][colIndex])
			{
				continue;
			}

			FVector tilePosition = m_startPosition;
			tilePosition.Y += (h + s) * rowIndex;
			if (0 != rowIndex % 2)
			{
				tilePosition.X += r;
			}
			tilePosition.X += 2 * r * colIndex;

			ATile* tile = world->SpawnActor<ATile>(m_tile->GeneratedClass, tilePosition, FRotator::ZeroRotator);
			tile->SetFolderPath("Map/Tiles");
			//TODO: Something is fucked with the indices of the template
			tile->initialize(FMapIndex(rowIndex, colIndex), MAP_TEMPLATE[rowIndex][colIndex], 0);
			if (ETileType::RESOURCE == MAP_TEMPLATE[rowIndex][colIndex])
			{
				int resourceIndex = FMath::RandRange(0, resources.Num() - 1);
				tile->setResource(resources[resourceIndex]);
				resources.RemoveAt(resourceIndex);
			}
			tiles[rowIndex][colIndex] = tile;
		}
	}
	ATileMap* tileMap = world->SpawnActor<ATileMap>(ATileMap::StaticClass());
	TTwoDArray<AIntersection*> intersections = generateIntersections(tiles, r, s, h);
	tileMap->initialize(MoveTemp(tiles), MoveTemp(intersections));

	world->GetGameState<ANotCatanGameState>()->setTileMap(tileMap);
}

TTwoDArray<AIntersection*> AMapGenerator::generateIntersections(const TTwoDArray<ATile*>& tiles, float tileR, float tileS, float tileH)
{
	TTwoDArray<AIntersection*> intersections(tiles.getRowLength() + 1, tiles.getColumLength() * 2 + 2);
	FVector intersectionStartPosition = m_startPosition;
	intersectionStartPosition.X -= tileR;
	intersectionStartPosition.Y -= tileS / 2;

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
				intersectionPosition.X += intersectionIndex.col * tileR;
				intersectionPosition.Y += intersectionIndex.row * (tileS + tileH);
				if (intersectionIndex.col % 2 != intersectionIndex.row % 2)
				{
					intersectionPosition.Y -= tileH;
				}

				AIntersection* intersecion = GetWorld()->SpawnActor<AIntersection>(m_intersection->GeneratedClass, intersectionPosition, FRotator::ZeroRotator);
				intersecion->SetFolderPath("Map/Intersections");
				intersecion->initialize(FMapIndex(intersectionIndex.row, intersectionIndex.col));
				intersections[intersectionIndex.row][intersectionIndex.col] = intersecion;
			}
		}
	}
	return intersections;

	/*for (int rowIndex = 0; rowIndex < intersections.getRowLength(); rowIndex++)
	{
		int intersectionsInRow = intersections.getColumLength();
		if (rowIndex == 0 || rowIndex == intersections.getRowLength() - 1)
		{
			intersectionsInRow -= 1;
		}
		for (int colIndex = 0; colIndex < intersectionsInRow; colIndex++)
		{
			FVector intersectionPosition = intersectionStartPosition;
			intersectionPosition.X += colIndex * tileR;
			intersectionPosition.Y += rowIndex * (tileS + tileH);
			if (colIndex % 2 != rowIndex % 2)
			{
				intersectionPosition.Y -= tileH;
			}

			AIntersection* intersecion = GetWorld()->SpawnActor<AIntersection>(m_intersection->GeneratedClass, intersectionPosition, FRotator::ZeroRotator);
			intersecion->SetFolderPath("Map/Intersections");
			intersecion->initialize(FMapIndex(colIndex, rowIndex));
			intersections[rowIndex][colIndex] = intersecion;
		}
	}
	return intersections;*/
}


FBox AMapGenerator::getTileBounds()
{
	UWorld* world = GetWorld();
	AActor* tile = world->SpawnActor<AActor>(m_tile->GeneratedClass, m_startPosition, FRotator::ZeroRotator);
	UStaticMeshComponent* tileMesh = Cast<UStaticMeshComponent>(tile->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	FBox boundingBox = tileMesh->Bounds.GetBox();
	tile->Destroy();
	return boundingBox;
}