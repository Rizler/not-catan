// Fill out your copyright notice in the Description page of Project Settings.

#include "Road.h"
#include "Net/UnrealNetwork.h"
#include "NotCatanPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"


// Sets default values
ARoad::ARoad()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> settlementMesh(TEXT("/Game/NotCatan/Meshes/AssetPack_Road"));
	m_roadMesh = settlementMesh.Object;
	m_meshComponent->SetStaticMesh(m_roadMesh);
}

void ARoad::initialize(const FRoadLocation& roadLocation, ANotCatanPlayerController* owningPlayer, bool isHighlighted = false)
{
	setOwningPlayer(owningPlayer);
	m_location = roadLocation;
	SetActorScale3D(FVector(9, 9, 9));
	if (isHighlighted)
	{
		highlight();
	}
	else
	{
		multicast_setMaterial(m_owningPlayer->getPlayerState()->getColor());
	}
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

void ARoad::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARoad, m_location);
}



/************************************ FRoadLocation ************************************/

FRoadLocation::FRoadLocation()
{}

FRoadLocation::FRoadLocation(const FMapIndex& intersectionIndex1, const FMapIndex& intersectionIndex2)
{
	this->intersectionIndex1 = intersectionIndex1;
	this->intersectionIndex2 = intersectionIndex2;
}

bool FRoadLocation::operator==(const FRoadLocation & other) const
{
	return ((intersectionIndex1 == other.intersectionIndex1 && intersectionIndex2 == other.intersectionIndex2) ||
		(intersectionIndex1 == other.intersectionIndex2 && intersectionIndex2 == other.intersectionIndex1));
}
