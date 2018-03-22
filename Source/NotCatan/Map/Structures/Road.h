// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Map/MapIndex.h"
#include "PlayerStructure.h"
#include "Road.generated.h"

class ANotCatanPlayerController;

USTRUCT()
struct FRoadLocation
{
	GENERATED_BODY()

public:
	FRoadLocation();
	FRoadLocation(const FMapIndex& intersectionIndex1, const FMapIndex& intersectionIndex2);

	FMapIndex intersectionIndex1;
	FMapIndex intersectionIndex2;

	bool operator==(const FRoadLocation& other) const;
};


UCLASS()
class NOTCATAN_API ARoad : public APlayerStructure
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoad();
	void initialize(const FRoadLocation& roadLocation, ANotCatanPlayerController* owningPlayer, bool isHighlighted /* = false */);
	bool isConnected(const ARoad& road) const;
	bool isOnIntersection(const FMapIndex& intersectionIndex) const;
	FRoadLocation getLocation() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Replicated)
	FRoadLocation m_location;
	UStaticMesh* m_roadMesh;

};


