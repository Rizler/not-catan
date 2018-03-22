// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "NotCatanPlayerController.h"
#include "PlayerStructure.h"
#include "IntersectionStructure.generated.h"

UCLASS()
class NOTCATAN_API AIntersectionStructure : public APlayerStructure
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntersectionStructure();
	UFUNCTION(BlueprintCallable)
	void initialize(ANotCatanPlayerController* owningPlayer);
	UFUNCTION(BlueprintPure)
	int32 getResourceYieldAmount() const;
	UFUNCTION(BlueprintCallable)
	void upgradeToCity();
	UFUNCTION(BlueprintCallable)
	bool isSettlement() const;

private:
	bool m_isSettlement;
	int32 m_resourceYieldAmount = 1;
	UStaticMesh* m_settlementMesh;
	UStaticMesh* m_cityMesh;
};
