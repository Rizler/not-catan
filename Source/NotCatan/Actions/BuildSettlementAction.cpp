#include "BuildSettlementAction.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "NotCatanPlayerController.h"
#include "NotCatanGameState.h"

ABuildSettlementAction::ABuildSettlementAction()
{}

ABuildSettlementAction::~ABuildSettlementAction()
{}

void ABuildSettlementAction::setValidBuildLocations(const TArray<FMapIndex>& validLocationss)
{
	m_validLocations = validLocationss;
}

void ABuildSettlementAction::onClick(AActor* hitActor)
{
	if (nullptr == hitActor || !hitActor->IsA(AIntersection::StaticClass()))
	{
		return;
	}
	
	AIntersection* intersection = Cast<AIntersection>(hitActor);
	if (m_validLocations.Contains(intersection->getMapIndex()))
	{
		highlightIntersections(false);
		server_buildSettlement(intersection->getMapIndex());
	}
}

void ABuildSettlementAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABuildSettlementAction, m_validLocations);
}

void ABuildSettlementAction::client_performAction_Implementation()
{
	highlightIntersections(true);
	setPlayerAction();
}

bool ABuildSettlementAction::server_buildSettlement_Validate(const FMapIndex& settlementLocation)
{
	return !m_wasSettlementBuilt && m_validLocations.Contains(settlementLocation);
}

void ABuildSettlementAction::server_buildSettlement_Implementation(const FMapIndex& settlementLocation)
{
	AIntersection* intersection = GetWorld()->GetGameState<ANotCatanGameState>()->getTileMap()->getIntersection(settlementLocation);
	intersection->buildSettlement(getPerformingPlayer());
	m_wasSettlementBuilt = true;
	broadcastPerformedEvent();
}

void ABuildSettlementAction::highlightIntersections(bool shouldHighlight)
{
	ATileMap* tileMap = GetWorld()->GetGameState<ANotCatanGameState>()->getTileMap();
	for (const FMapIndex& intersectionIndex : m_validLocations)
	{
		tileMap->getIntersection(intersectionIndex)->highlight(shouldHighlight);
	}
}
