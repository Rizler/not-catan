// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "NotCatanTypes.h"
#include "Intersection.h"
#include "TwoDArray.h"
#include "MapGenerator.generated.h"

UCLASS()
class NOTCATAN_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FVector m_startPosition;
	UPROPERTY(EditAnywhere, Category = "Blueprints")
	UBlueprint* m_tile;
	UPROPERTY(EditAnywhere, Category = "Blueprints")
	UBlueprint* m_intersection;
	
public:	
	// Sets default values for this actor's properties
	AMapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	TArray<EResource> getResources();
	void generateMap();
	TTwoDArray<AIntersection*> AMapGenerator::generateIntersections(const TTwoDArray<ATile*>& tiles, float tileR, float tileS, float tileH);
	FBox getTileBounds();

	static constexpr uint8  MAP_SIZE = 7;
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
