// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Map/MapIndex.h"
#include "Road.generated.h"

class ANotCatanPlayerController;

USTRUCT()
struct FRoadLocation
{
	GENERATED_BODY()

public:
	FMapIndex intersectionIndex1;
	FMapIndex intersectionIndex2;

	bool operator==(const FRoadLocation& other);
};


UCLASS()
class NOTCATAN_API ARoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoad();
	void initialize(const FRoadLocation& roadLocation, ANotCatanPlayerController* owner, bool isHighlighted /* = false */);
	bool isConnected(const ARoad& road) const;
	bool isOnIntersection(const FMapIndex& intersectionIndex) const;
	FRoadLocation getLocation() const;
	const ANotCatanPlayerController* getOwner() const;

private:
	ANotCatanPlayerController* m_owner;
	FRoadLocation m_location;
};


