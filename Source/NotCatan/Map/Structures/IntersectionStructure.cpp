// Fill out your copyright notice in the Description page of Project Settings.

#include "IntersectionStructure.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AIntersectionStructure::AIntersectionStructure()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	m_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	m_meshComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> settlementMesh(TEXT("/Game/NotCatan/Meshes/AssetPack_Settlement"));
	m_settlementMesh = settlementMesh.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cityMesh(TEXT("/Game/NotCatan/Meshes/AssetPack_City"));
	m_cityMesh = cityMesh.Object;

	m_meshComponent->SetStaticMesh(m_settlementMesh);
}

void AIntersectionStructure::initialize(ANotCatanPlayerController* owningPlayer)
{
	m_owningPlayer = owningPlayer;
	m_isSettlement = true;
	
	SetActorScale3D(FVector(9, 9, 9));

	m_meshMaterial = UMaterialInstanceDynamic::Create(m_meshComponent->GetStaticMesh()->GetMaterial(0), m_meshComponent->GetStaticMesh());
	m_meshMaterial->SetVectorParameterValue("Color", m_owningPlayer->getPlayerState()->getColor());
	m_meshComponent->SetMaterial(0, m_meshMaterial);
	m_meshComponent->SetStaticMesh(m_settlementMesh);
	m_owningPlayer->getPlayerState()->increaseVictoryPoints(1);
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
	m_owningPlayer->getPlayerState()->increaseVictoryPoints(1);
	m_meshComponent->SetStaticMesh(m_cityMesh);
}

bool AIntersectionStructure::isSettlement() const
{
	return m_isSettlement;
}

void AIntersectionStructure::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AIntersectionStructure, m_meshComponent);
	DOREPLIFETIME(AIntersectionStructure, m_meshMaterial);
}

void AIntersectionStructure::onRep_meshComponent()
{
}

void AIntersectionStructure::onRep_meshMaterial()
{
}
