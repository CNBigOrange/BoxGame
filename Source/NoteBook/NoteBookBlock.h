// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteBook/public/TextureMaps.h"
#include "NoteBook/public/BoxManeger.h"
#include "NoteBook/public/BoxManegerLevel1.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "NoteBookBlock.generated.h"


/** A block that can be clicked */
UCLASS(minimalapi)
class ANoteBookBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;


public:
	ANoteBookBlock();

	/** Are we currently active? */
	bool bIsActive;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/** Pointer to blue material used on inactive blocks */
	UPROPERTY()
	class UMaterialInstance* TextureMaterial;

	/** Pointer to orange material used on active blocks */
	UPROPERTY()
	class UMaterialInstance* PostMaterial;

	/** Grid that owns us */
	UPROPERTY()
	class ANoteBookBlockGrid* OwningGrid;//

	UPROPERTY()
	class ABoxManeger* OwningManager;//Box管理者

	UPROPERTY()
	class ABoxManegerLevel1* OwningManager2;//Box管理者

	UPROPERTY(EditAnyWhere)
	FName Tag = "BlockBox";

	UPROPERTY(EditAnyWhere)
	FName LevelToLoad = "Level2";

	UPROPERTY()
	FLatentActionInfo LatentInfo;

	UPROPERTY()
	F_NumPair BoxInfo;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	USoundCue* ClickSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	USoundCue* RemoveSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UAudioComponent* AC;

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	
	template <typename T1>
	UFUNCTION()
	void HandleBoxArray(T1 Manager, ANoteBookBlock* self,int32 T2);



	void HandleClicked();

	void Highlight(bool bOn);

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};



