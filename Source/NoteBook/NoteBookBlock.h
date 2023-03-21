// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteBook/public/TextureMaps.h"
#include "NoteBook/public/BoxManeger.h"
#include "NoteBook/public/BoxManegerLevel1.h"
#include "NoteBook/public/BoxManegerLevel2.h"
#include "NoteBook/public/BaseBoxManegerLevel3.h"
#include "NoteBook/public/MyBoxGameSubsystem.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "NoteBookBlock.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBoxesDelete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickBoxDelete);

class UBoxComponent;
/** A block that can be clicked */
UCLASS(minimalapi)
class ANoteBookBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class USceneComponent* DummyRoot;
	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class USceneComponent* SceneC;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

	//UPROPERTY(Category = Block, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class UBoxComponent* BoxCollision;
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
	class ABaseBoxManeger* OwningManagerBase;//Box管理者

	UPROPERTY()
	class ABoxManeger* OwningManager;//Box管理者

	UPROPERTY()
	class ABoxManegerLevel1* OwningManagerLevel1;//Box管理者

	UPROPERTY()
	class ABoxManegerLevel2* OwningManagerLevel2;//Box管理者

	UPROPERTY()
	class ABaseBoxManegerLevel3* OwningManagerLevel3;//Box管理者

	UPROPERTY(EditAnyWhere)
	FName Tag = "BlockBox";

	UPROPERTY(EditAnyWhere)
	FName Level2 = "Level2";

	UPROPERTY()
	FLatentActionInfo LatentInfo;

	UPROPERTY(BlueprintReadOnly)
	F_NumPair BoxInfo;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	USoundCue* ClickSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	USoundCue* RemoveSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UAudioComponent* AC;

	//实例化代理
	UPROPERTY(BlueprintAssignable)
    FOnBoxesDelete OnBoxesDelete;

	UPROPERTY(BlueprintAssignable)
	FOnClickBoxDelete OnClickBox;

	/** Handle the block being clicked */
	UFUNCTION(BlueprintCallable)
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	
	template <typename T1>
	UFUNCTION()
	void HandleBoxArray(T1 Manager, ANoteBookBlock* self,FName Level);

	template <typename T1>
	UFUNCTION()
	void HandleSameBoxArray3(T1 Manager, ANoteBookBlock* self, FName Level);

	template <typename T1>
	UFUNCTION()
	void HandleSameBoxArray2(T1 Manager, ANoteBookBlock* self, FName Level);
	UFUNCTION(BlueprintCallable)
	void HandleClicked();

	void Highlight(bool bOn);

protected:

	UFUNCTION()
		void GetCurrentBoxNums(int32 Nums);

	UFUNCTION()
		void AddScore(int32 Nums);


public:
	/** Returns DummyRoot subobject **/
	//FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};



