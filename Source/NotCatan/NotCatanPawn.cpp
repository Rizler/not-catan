// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NotCatanPawn.h"
#include "NotCatanBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ANotCatanPawn::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);

	/*if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		FVector Start, Dir, End;
		playerController->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f);
		TraceForBlock(Start, End, false);
	}*/
}

void ANotCatanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MouseLeftClick", EInputEvent::IE_Pressed, this, &ANotCatanPawn::onMouseClick);
}

void ANotCatanPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	//OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void ANotCatanPawn::setAction(AAction* action)
{
	m_action = action;
}

void ANotCatanPawn::onMouseClick()
{
	if (nullptr == m_action)
	{
		return;
	}

	FVector start, dir, end;
	APlayerController* playerController = Cast<APlayerController>(GetController());
	playerController->DeprojectMousePositionToWorld(start, dir);
	end = start + (dir * 8000.0f);
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility);
	DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red);
	//DrawDebugSolidBox(GetWorld(), hitResult.Location, FVector(20.0f), FColor::Red);
	m_action->onClick(hitResult.GetActor());

	/*if (CurrentBlockFocus)
	{
		CurrentBlockFocus->HandleClicked();
	}*/
}

void ANotCatanPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult hitResult;
	GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), hitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (nullptr != hitResult.GetActor())
	{
		ANotCatanBlock* HitBlock = Cast<ANotCatanBlock>(hitResult.GetActor());
		if (CurrentBlockFocus != HitBlock)
		{
			if (CurrentBlockFocus)
			{
				CurrentBlockFocus->Highlight(false);
			}
			if (HitBlock)
			{
				HitBlock->Highlight(true);
			}
			CurrentBlockFocus = HitBlock;
		}
	}
	else if (CurrentBlockFocus)
	{
		CurrentBlockFocus->Highlight(false);
		CurrentBlockFocus = nullptr;
	}
}