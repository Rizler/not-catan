// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildRoadAction.h"
#include "Net/UnrealNetwork.h"
#include "NotCatanGameState.h"

ABuildRoadAction::~ABuildRoadAction()
{}

void ABuildRoadAction::setValidBuildLocations(const TArray<FRoadLocation>& validLocationss)
{
	m_validLocations = validLocationss;
}

void ABuildRoadAction::onClick(AActor* hitActor)
{
	if (nullptr == hitActor || !hitActor->IsA(ARoad::StaticClass()))
	{
		return;
	}

	ARoad* road = Cast<ARoad>(hitActor);
	if (m_validLocations.Contains(road->getLocation()))
	{
		destroyHighlightedRoads();
		server_buildRoad(road->getLocation());
	}
}

void ABuildRoadAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABuildRoadAction, m_validLocations);
}

void ABuildRoadAction::client_perform_Implementation()
{
	Super::client_perform_Implementation();

	highlightRoads();
}

bool ABuildRoadAction::server_buildRoad_Validate(const FRoadLocation& roadLocation)
{
	return m_validLocations.Contains(roadLocation);
}

void ABuildRoadAction::server_buildRoad_Implementation(const FRoadLocation& roadLocation)
{
	ATileMap* tileMap = GetWorld()->GetGameState<ANotCatanGameState>()->getTileMap();
	tileMap->buildRoad(roadLocation, getPerformingPlayer(), false);
	m_validLocations.Empty();
	broadcastPerformedEvent();
}

void ABuildRoadAction::highlightRoads()
{
	ATileMap* tileMap = GetWorld()->GetGameState<ANotCatanGameState>()->getTileMap();
	for (const FRoadLocation& potentialRoadLocation : m_validLocations)
	{
		ARoad* road = tileMap->buildRoad(potentialRoadLocation, getPerformingPlayer(), true);
		m_highlightedRoads.Add(road);
	}
}

void ABuildRoadAction::destroyHighlightedRoads()
{
	for (ARoad* road : m_highlightedRoads)
	{
		road->Destroy();
	}
}
