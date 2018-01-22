// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NotCatanTypes.h"
#include "Tile.h"
#include "Intersection.h"
#include "../TwoDArray.h"
#include "Tile.h"
#include "Intersection.h"
#include "MapGenerator.generated.h"

UCLASS()
class NOTCATAN_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGenerator();

	UFUNCTION(BlueprintCallable)
	void randomiseResources();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Blueprints")
	TSubclassOf<ATile> m_tile;
	UPROPERTY(EditAnywhere, Category = "Blueprints")
	TSubclassOf<AIntersection> m_intersection;

private: 
	UFUNCTION()
	TArray<EResource> getResources();
	UFUNCTION()
	void calculateTileProperties();
	UFUNCTION()
	void generateMap();
	UFUNCTION()
	FBox getTileBounds();
	TTwoDArray<AIntersection*> AMapGenerator::generateIntersections(const TTwoDArray<ATile*>& tiles);

	TTwoDArray<ATile*> m_tiles;
	UPROPERTY()
	TArray<AActor*> aactors;
	FVector m_mapTopLeftPosition;
	/*
		hexagon properties:
		https://www.gamedev.net/articles/programming/general-and-gameplay-programming/coordinates-in-hexagon-based-tile-maps-r1800/	
	*/
	float m_tileA;
	float m_tileB;
	float m_tileS;
	float m_tileH;
	float m_tileR;
	static constexpr uint8 MAP_SIZE = 7;
	static constexpr ETileType MAP_TEMPLATE[MAP_SIZE][MAP_SIZE] =
	{
		{ETileType::NONE,	ETileType::NONE,		ETileType::SEA,			ETileType::SEA,			ETileType::SEA,			ETileType::SEA,			ETileType::NONE},
		{ETileType::NONE,	ETileType::SEA,			ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::SEA,			ETileType::NONE},
		{ETileType::NONE,	ETileType::SEA,			ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::SEA},
		{ETileType::SEA,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::SEA},
		{ETileType::NONE,	ETileType::SEA,			ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::SEA},
		{ETileType::NONE,	ETileType::SEA,			ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::RESOURCE,	ETileType::SEA,			ETileType::NONE},
		{ETileType::NONE,	ETileType::NONE,		ETileType::SEA,			ETileType::SEA,			ETileType::SEA,			ETileType::SEA,			ETileType::NONE},
	};
	
};
