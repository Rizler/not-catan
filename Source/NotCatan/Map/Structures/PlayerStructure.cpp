#include "PlayerStructure.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"


// Sets default values
APlayerStructure::APlayerStructure()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bAlwaysRelevant = true;

	m_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	m_meshComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> highlightMaterial(TEXT("/Game/NotCatan/Materials/M_Highlight"));
	m_highlightMaterial = highlightMaterial.Object;
}

APlayerStructure::~APlayerStructure()
{}

ANotCatanPlayerController * APlayerStructure::getOwningPlayer() const
{
	return m_owningPlayer;
}

void APlayerStructure::highlight()
{
	this->SetReplicates(false);
	m_meshComponent->SetMaterial(0, m_highlightMaterial);
}

void APlayerStructure::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStructure, m_meshComponent);
	DOREPLIFETIME(APlayerStructure, m_meshMaterial);
}

void APlayerStructure::setOwningPlayer(ANotCatanPlayerController * owningPlayer)
{
	m_owningPlayer = owningPlayer;
}

void APlayerStructure::multicast_setMaterial_Implementation(const FColor& color)
{
	m_meshMaterial = UMaterialInstanceDynamic::Create(m_meshComponent->GetStaticMesh()->GetMaterial(0), m_meshComponent->GetStaticMesh());
	m_meshMaterial->SetVectorParameterValue("Color", color);
	m_meshComponent->SetMaterial(0, m_meshMaterial);
}
