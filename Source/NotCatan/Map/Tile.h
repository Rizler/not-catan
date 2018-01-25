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
	void BeginPlay() override;
	UFUNCTION()
	void initialize(const FMapIndex& mapIndex, ETileType type, int number);
	UFUNCTION()
	void setResource(EResource resource);
	UFUNCTION()
	FMapIndex getMapIndex() const;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void onRep_resource();
	UFUNCTION()
	virtual void onRep_number();

protected:
	UFUNCTION(BlueprintNativeEvent)
	void updateMaterial();
	
	UPROPERTY(Replicated, BlueprintReadOnly)
	ETileType m_tileType;
	UPROPERTY(ReplicatedUsing = onRep_resource, BlueprintReadOnly)
	EResource m_resource;

private:
	UPROPERTY(Replicated)
	FMapIndex m_mapIndex;
	UPROPERTY(ReplicatedUsing = onRep_number)
	int m_number;
};
