// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NotCatanTypes.h"
#include "MapIndex.h"
#include "Tile.generated.h"

UCLASS()
class NOTCATAN_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	void initialize(const FMapIndex& mapIndex, ETileType type, int number);
	void setResource(EResource resource);
	FMapIndex getMapIndex() const;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void updateMaterial();
	UPROPERTY(BlueprintReadOnly)
	ETileType m_tileType;
	UPROPERTY(BlueprintReadOnly)
	EResource m_resource;


private:
	FMapIndex m_mapIndex;
	int m_number;
};
