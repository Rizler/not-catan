#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Action.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionPerformed);

UCLASS(abstract)
class NOTCATAN_API AAction : public AActor
{
	GENERATED_BODY()

public:
	AAction();
	virtual ~AAction();
	
	UFUNCTION()
	virtual class ANotCatanPlayerController* getPerformingPlayer();
	UFUNCTION()
	virtual void onClick(AActor* hitResult);
	UFUNCTION()
	virtual void setPlayerAction();
	UFUNCTION()
	virtual void removePlayerAction();

	FActionPerformed actionPreformedEvent;

protected:
	UFUNCTION()
	void broadcastPerformedEvent();
};

