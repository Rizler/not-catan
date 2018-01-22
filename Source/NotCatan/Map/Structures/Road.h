// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Map/MapIndex.h"
#include "Road.generated.h"

UCLASS()
class NOTCATAN_API ARoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoad();
	void initialize(const FMapIndex& intersectionIndex1, const FMapIndex& intersectionIndex2);
	bool isConnected(const ARoad& road) const;
	bool isOnIntersection(const FMapIndex& intersectionIndex) const;

private:
	FMapIndex m_intersectionIndex1;
	FMapIndex m_intersectionIndex2;
};
