#include "Action.h"
#include "NotCatanPlayerController.h"

AAction::AAction()
{
	bReplicates = true;
	bOnlyRelevantToOwner = true;
}

AAction::~AAction()
{
}

ANotCatanPlayerController* AAction::getPerformingPlayer()
{
	return Cast<ANotCatanPlayerController>(GetOwner());
}

void AAction::onClick(AActor* hitActor)
{
}

void AAction::broadcastPerformedEvent()
{
	actionPreformedEvent.Broadcast(this);
}

void AAction::setPlayerAction()
{
	getPerformingPlayer()->setAction(this);
}

void AAction::removePlayerAction()
{
	getPerformingPlayer()->setAction(nullptr);
}

void AAction::client_perform_Implementation()
{
	setPlayerAction();
}
