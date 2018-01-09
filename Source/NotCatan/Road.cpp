// Fill out your copyright notice in the Description page of Project Settings.

#include "Road.h"


// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ARoad::initialize(const FMapIndex& intersectionIndex1, const FMapIndex& intersectionIndex2)
{
	m_intersectionIndex1 = intersectionIndex1;
	m_intersectionIndex2 = intersectionIndex2;
}

bool ARoad::isConnected(const ARoad& road) const
{
	return (road.isOnIntersection(m_intersectionIndex1) || road.isOnIntersection(m_intersectionIndex2));
}

bool ARoad::isOnIntersection(const FMapIndex& intersectionIndex) const
{
	return (intersectionIndex == m_intersectionIndex1 || intersectionIndex == m_intersectionIndex2);
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}