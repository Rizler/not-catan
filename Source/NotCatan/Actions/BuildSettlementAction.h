#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Map/MapIndex.h"
#include "BuildSettlementAction.generated.h"

UCLASS()
class NOTCATAN_API ABuildSettlementAction : public AAction
{
	GENERATED_BODY()

public:
	ABuildSettlementAction();
	virtual ~ABuildSettlementAction();

	virtual void setValidBuildLocations(const TArray<FMapIndex>& validLocationss);
	virtual void onClick(AActor* hitActor) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Client, Reliable)
	void client_performAction();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void server_buildSettlement(const FMapIndex& settlementLocation);
	bool server_buildSettlement_Validate(const FMapIndex& settlementLocation);
	void server_buildSettlement_Implementation(const FMapIndex& settlementLocation);

private:
	UPROPERTY(Replicated)
	TArray<FMapIndex> m_validLocations;
	bool m_wasSettlementBuilt;

	void highlightIntersections(bool shouldHighlight);
};