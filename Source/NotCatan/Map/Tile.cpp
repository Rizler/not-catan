// Fill out your copyright notice in the Description page of Project Settings.
#include "Tile.h"
#include "Net/UnrealNetwork.h"
#include "Engine.h"


// Sets default values
ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bAlwaysRelevant = true;
}

void ATile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATile, m_tileType);
	DOREPLIFETIME(ATile, m_resource);
	DOREPLIFETIME(ATile, m_mapIndex);
	DOREPLIFETIME(ATile, m_number);
}

void ATile::BeginPlay()
{
	Super::BeginPlay();

	//TODO: Setting scale manually because it is replicated wrong
	SetActorScale3D(FVector(0.08f, 0.08f, 0.08f));
	updateMaterial();
}

void ATile::initialize(const FMapIndex& mapIndex, ETileType type, int number)
{
	m_mapIndex = mapIndex;
	m_tileType = type;
	m_number = number;
}

void ATile::setResource(EResource resource)
{
	m_resource = resource;
	updateMaterial();
}

FMapIndex ATile::getMapIndex() const
{
	return m_mapIndex;
}

void ATile::updateMaterial_Implementation()
{}

void ATile::onRep_resource()
{
	updateMaterial();
}

void ATile::onRep_number()
{

}