// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "NoteBookBlockGrid.generated.h"

/** Class used to spawn blocks and manage score */
class ANoteBookBlock;//头文件前置声明

UCLASS(minimalapi)
class ANoteBookBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot2;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

public:
	ANoteBookBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 XSize;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 YSize;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 ZSize;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	UFUNCTION()
	bool SetBlockOwner(ANoteBookBlock* NewBlock);

	UFUNCTION()
	void SpawnBox();

public:

	/** Handle the block being clicked */
	void AddScore();

	/*Restart*/
	UFUNCTION(BlueprintCallable)
	void Restart(int32 x,int32 y,int32 z);

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
};



