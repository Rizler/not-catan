// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Action.h"
#include "Map/MapIndex.h"
#include "Map/Structures/Road.h"
#include "BuildRoadAction.generated.h"

UCLASS()
class NOTCATAN_API ABuildRoadAction : public AAction
{
	GENERATED_BODY()
	
public:
	virtual ~ABuildRoadAction();

	virtual void setValidBuildLocations(const TArray<FRoadLocation>& validLocationss);
	virtual void onClick(AActor* hitActor) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void client_perform_Implementation() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void server_buildRoad(const FRoadLocation& roadLocation);
	bool server_buildRoad_Validate(const FRoadLocation& roadLocation);
	void server_buildRoad_Implementation(const FRoadLocation& roadLocation);

private:
	UPROPERTY(Replicated)
	TArray<FRoadLocation> m_validLocations;
	TArray<ARoad*> m_highlightedRoads;

	void highlightRoads();
	void destroyHighlightedRoads();
};
