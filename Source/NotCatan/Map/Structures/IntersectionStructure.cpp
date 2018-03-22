// Fill out your copyright notice in the Description page of Project Settings.

#include "IntersectionStructure.h"
#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AIntersectionStructure::AIntersectionStructure()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> settlementMesh(TEXT("/Game/NotCatan/Meshes/AssetPack_Settlement"));
	m_settlementMesh = settlementMesh.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cityMesh(TEXT("/Game/NotCatan/Meshes/AssetPack_City"));
	m_cityMesh = cityMesh.Object;
	m_meshComponent->SetStaticMesh(m_settlementMesh);
}

void AIntersectionStructure::initialize(ANotCatanPlayerController* owningPlayer)
{
	setOwningPlayer(owningPlayer);
	m_isSettlement = true;
	SetActorScale3D(FVector(9, 9, 9));
	multicast_setMaterial(m_owningPlayer->getPlayerState()->getColor());
}

int32 AIntersectionStructure::getResourceYieldAmount() const
{
	if (m_isSettlement)
	{
		return 1;
	}
	return 2;
}

void AIntersectionStructure::upgradeToCity()
{
	m_isSettlement = false;
	m_meshComponent->SetStaticMesh(m_cityMesh);
}

bool AIntersectionStructure::isSettlement() const
{
	return m_isSettlement;
}