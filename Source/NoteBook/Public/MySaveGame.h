// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class NOTEBOOK_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
		UPROPERTY(VisibleAnyWhere, Category = Basic)
		int Level = 1;

		UPROPERTY(VisibleAnyWhere, Category = Basic)
		FString SaveSlotName;

		UPROPERTY(VisibleAnyWhere, Category = Basic)
		uint32 UserIndex;

		UMySaveGame();
};
