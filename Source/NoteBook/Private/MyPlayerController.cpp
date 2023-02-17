// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "NoteBook/NoteBookBlock.h"
#include "NoteBook/NoteBookBlockGrid.h"
#include "Camera/CameraComponent.h"


AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

