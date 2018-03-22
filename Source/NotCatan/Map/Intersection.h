// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapIndex.h"
#include "Structures/IntersectionStructure.h"
#include "Intersection.generated.h"

UCLASS()
class NOTCATAN_API AIntersection : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIntersection();
	void initialize(const FMapIndex& mapIndex);
	FMapIndex getMapIndex() const;
	bool isValidBuildLocation(uint32 playerId) const;
	const AIntersectionStructure* getStructure() const;
	void buildSettlement(ANotCatanPlayerController* owner);
	UFUNCTION(BlueprintNativeEvent)
	void highlight(bool shouldHighlight);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Replicated)
	FMapIndex m_mapIndex;
	UPROPERTY(Replicated)
	AIntersectionStructure* m_structure;
};
