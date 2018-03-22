// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Map/Structures/PlayerStructureCount.h"
#include "NotCatanPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerSateChanged);

UCLASS()
class NOTCATAN_API ANotCatanPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	FString getName() const;
	UFUNCTION()
	void setName(const FString& name);
	
	UFUNCTION(BlueprintPure)
	int32 getVictoryPoints() const;
	UFUNCTION()
	void setVictoryPoints(int32 victoryPoints);
	UFUNCTION()
	void increaseVictoryPoints(int32 victoryPoints);

	UFUNCTION(BlueprintPure)
	int32 getResourcesCount() const;
	UFUNCTION(BlueprintPure)
	int32 getDevelopmentCardsCount() const;

	UFUNCTION(BlueprintPure)
	FColor getColor() const;
	UFUNCTION()
	void setColor(const FColor& color);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Replication methods - called on client
	UFUNCTION()
	virtual void onRep_victoryPoints();
	UFUNCTION()
	virtual void onRep_color();
	UFUNCTION()
	virtual void onRep_name();

	// Members
	UPROPERTY(BlueprintAssignable)
	FPlayerSateChanged m_playerStateChanged;
	
private:
	UPROPERTY(ReplicatedUsing = onRep_name)
	FString m_name;
	UPROPERTY(ReplicatedUsing = onRep_victoryPoints)
	int32 m_victoryPoints;
	UPROPERTY(Replicated)
	int32 m_resourcesCount;
	UPROPERTY(Replicated)
	int32 m_developmentCardsCount;
	UPROPERTY(ReplicatedUsing = onRep_color)
	FColor m_color;
	UPROPERTY(Replicated)
	FPlayerStructureCount m_structureCount;
};
