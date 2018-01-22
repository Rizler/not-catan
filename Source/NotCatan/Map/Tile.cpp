// Fill out your copyright notice in the Description page of Project Settings.
#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
{

}
