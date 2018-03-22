#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "NotCatanPlayerController.h"
#include "PlayerStructure.generated.h"

UCLASS(abstract)
class NOTCATAN_API APlayerStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayerStructure();
	virtual ~APlayerStructure();

	virtual ANotCatanPlayerController* getOwningPlayer() const;
	virtual void highlight();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION(NetMulticast, Reliable)
	virtual void multicast_setMaterial(const FColor& color);
	

protected:
	UFUNCTION()
	virtual void setOwningPlayer(ANotCatanPlayerController* owningPlayer);

	UPROPERTY()
	ANotCatanPlayerController* m_owningPlayer;
	UPROPERTY(Replicated)
	UStaticMeshComponent* m_meshComponent;
	UPROPERTY(Replicated)
	UMaterialInstanceDynamic* m_meshMaterial;
	UPROPERTY()
	UMaterial* m_highlightMaterial;

};
