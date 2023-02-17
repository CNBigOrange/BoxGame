// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoteBookGameMode.h"
#include "MyPlayerController.h"
#include "MyPawn.h"

ANoteBookGameMode::ANoteBookGameMode()
{
	// no pawn by default
	DefaultPawnClass = AMyPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
