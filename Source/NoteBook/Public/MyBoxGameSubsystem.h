// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MySaveGame.h"
#include "MyBoxGameSubsystem.generated.h"


class ANoteBookBlock;
UCLASS()
class NOTEBOOK_API UMyBoxGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
		void Initi();

	UFUNCTION()
		void SetCurrentBoxNums();

	UFUNCTION()
		void AddScore();

	UFUNCTION(BlueprintCallable)
		void SaveGameData(int current_level);

	UFUNCTION(BlueprintCallable)
		const int & LoadingGameData();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetBoxNums() { return BoxNums; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetScore() { return Score; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameData")
		int32 BoxNums;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameData")
		int32 Score;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameData")
		ANoteBookBlock* Box;

protected:
	int i = -1;

};
