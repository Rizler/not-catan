// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "NotCatanPlayerController.h"
#include "IntersectionStructure.generated.h"

UCLASS()
class NOTCATAN_API AIntersectionStructure : public AActor
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
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void onRep_meshComponent();
	UFUNCTION()
	void onRep_meshMaterial();

private:
	ANotCatanPlayerController* m_owningPlayer;
	bool m_isSettlement;
	int32 m_resourceYieldAmount = 1;
	UStaticMesh* m_settlementMesh;
	UStaticMesh* m_cityMesh;
	UPROPERTY(ReplicatedUsing = onRep_meshComponent)
	UStaticMeshComponent* m_meshComponent;
	UPROPERTY(ReplicatedUsing = onRep_meshMaterial)
	UMaterialInstanceDynamic* m_meshMaterial;
};
