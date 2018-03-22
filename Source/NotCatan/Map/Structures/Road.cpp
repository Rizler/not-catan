// Fill out your copyright notice in the Description page of Project Settings.

#include "Road.h"
#include "NotCatanPlayerController.h"


// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ARoad::initialize(const FRoadLocation& roadLocation, ANotCatanPlayerController* owner, bool isHighlighted = false)
{
	m_location = roadLocation;
	m_owner = owner;
	
}

bool ARoad::isConnected(const ARoad& road) const
{
	return (road.isOnIntersection(m_location.intersectionIndex1) || road.isOnIntersection(m_location.intersectionIndex2));
}

bool ARoad::isOnIntersection(const FMapIndex& intersectionIndex) const
{
	return (intersectionIndex == m_location.intersectionIndex1 || intersectionIndex == m_location.intersectionIndex2);
}

FRoadLocation ARoad::getLocation() const
{
	return m_location;
}

const ANotCatanPlayerController* ARoad::getOwner() const
{
	return m_owner;
}


bool FRoadLocation::operator==(const FRoadLocation & other)
{
	return ((intersectionIndex1 == other.intersectionIndex1 && intersectionIndex2 == other.intersectionIndex2) ||
		(intersectionIndex1 == other.intersectionIndex2 && intersectionIndex2 == other.intersectionIndex1));
}
