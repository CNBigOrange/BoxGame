// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoteBookBlock.h"
#include "NoteBookBlockGrid.h"
#include "UObject/ConstructorHelpers.h"//加载资源方式，ConstructorHelpers只能在构造函数中使用。
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ANoteBookBlock::ANoteBookBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> TextureMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> CheckedMaterial;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> ClickSoundInst;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> RemoveSoundInst;
		FConstructorStatics(): PlaneMesh(TEXT("/Game/Geometry/Meshes/Box/Box.Box"))
			, BaseMaterial(TEXT("/Game/Geometry/Meshes/Box/Material_001.Material_001"))
			, TextureMaterial(TEXT("/Game/Geometry/Meshes/Box/Material_002_Inst.Material_002_Inst"))
			, CheckedMaterial(TEXT("/Game/Geometry/Meshes/Box/M_CheckedMaterial_Inst.M_CheckedMaterial_Inst"))
			, ClickSoundInst(TEXT("/Game/Music/ClickSound.ClickSound"))
			, RemoveSoundInst(TEXT("/Game/Music/RemoveSound.RemoveSound"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.1f,0.1f,0.1f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetRelativeRotation(FRotator(0.f, 0.f, 180.f));//FRotator
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	BlockMesh->SetMaterial(1, ConstructorStatics.TextureMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ANoteBookBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ANoteBookBlock::OnFingerPressedBlock);
	BlockMesh->SetRenderCustomDepth(false);
	BlockMesh->SetSimulatePhysics(false);


	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	TextureMaterial = ConstructorStatics.TextureMaterial.Get();
	PostMaterial = ConstructorStatics.CheckedMaterial.Get();

	//Sound
	ClickSound = ConstructorStatics.ClickSoundInst.Get();
	RemoveSound = ConstructorStatics.RemoveSoundInst.Get();

}

void ANoteBookBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ANoteBookBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void ANoteBookBlock::HandleClicked()
{
	// Check we are not already active
	if (!bIsActive)
	{
		bIsActive = true;

		// Change material
		//BlockMesh->SetMaterial(0, PostMaterial);
		this->BlockMesh->SetMaterial(0, PostMaterial);
		//BlockMesh->SetRenderCustomDepth(true);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, BoxInfo.Type);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::FromInt(BoxInfo.TypeNum));

		if (ClickSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ClickSound, this->GetActorLocation());
		}

		if (OwningManagerLevel2) {
			HandleSameBoxArray<ABoxManegerLevel2*>(OwningManagerLevel2, this , "Level3");
			//UE_LOG(LogTemp,Display,TEXT(""))
		}
		else if (OwningManagerLevel1) {
			HandleSameBoxArray<ABoxManegerLevel1*>(OwningManagerLevel1, this , "Level2");
		}
		else if (OwningManagerLevel3) {
			HandleSameBoxArray<ABaseBoxManegerLevel3*>(OwningManagerLevel3, this, "Level_Demo");
		}
		else if (OwningManager) {
			HandleBoxArray<ABoxManeger*>(OwningManager, this, "Level_Demo");
			UE_LOG(LogTemp, Display, TEXT("OwningManager"));
		}
	}

}

void ANoteBookBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (bIsActive)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, PostMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
}

template <typename T1>
void ANoteBookBlock::HandleBoxArray(T1 Manager, ANoteBookBlock* self , FName Level)
{
	if (!self) return;

	Manager->Boxes.Add(self);
	auto BoxArray = Manager->Boxes;

	UE_LOG(LogTemp, Display, TEXT("%i"), BoxArray.Num());


	if (BoxArray.Num() == 3)
	{
		UE_LOG(LogTemp, Display, TEXT("%i"), BoxArray.Num());

		if (BoxArray[0] == nullptr && BoxArray[1] == nullptr && BoxArray[2] == nullptr)
		{
			Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 10; });
			UE_LOG(LogTemp, Display, TEXT("nullptr"));
			return;
		};

		if (BoxArray[0]->BoxInfo.Type== BoxArray[1]->BoxInfo.Type&& BoxArray[1]->BoxInfo.Type == BoxArray[2]->BoxInfo.Type)
		{
			UE_LOG(LogTemp, Display, TEXT("Same Type"));
			BoxArray.Sort([](const ANoteBookBlock& A, const ANoteBookBlock& B) {
				return A.BoxInfo.TypeNum < B.BoxInfo.TypeNum; });//lambda函数
			
			if (BoxArray[0]->BoxInfo.TypeNum == BoxArray[1]->BoxInfo.TypeNum &&
				BoxArray[2]->BoxInfo.TypeNum == BoxArray[1]->BoxInfo.TypeNum)
			{
				for (auto Box : BoxArray) {
					//消除选中的盒子
					GetWorld()->DestroyActor(Box, false, false);
					OnBoxesDelete.Broadcast();
				}
				Manager->BoxesNum = Manager->BoxesNum - 3;

				if (ClickSound && RemoveSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), RemoveSound, this->GetActorLocation());
				}
				UE_LOG(LogTemp, Display, TEXT("Same Box"));
				Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 10; });
				//相同消除加分


				//判断是否通关
				if (Manager->BoxesNum == 0)
				{
					Manager->IsSuc = true;
					//OwningManager->ShowWinWBP();
					//UGameplaystatics::LoadStreamLevel(this,LevelToLoad,true,true, LatentInfo);
					UGameplayStatics::OpenLevel(GetWorld(), Level);
				}
			}
			else if (BoxArray[0]->BoxInfo.TypeNum + 1 == BoxArray[1]->BoxInfo.TypeNum &&
					 BoxArray[2]->BoxInfo.TypeNum - 1 ==  BoxArray[1]->BoxInfo.TypeNum)
			{
				for (auto Box : BoxArray) {
					//消除选中的盒子
					GetWorld()->DestroyActor(Box, false, false);
					OnBoxesDelete.Broadcast();
				}
				Manager->BoxesNum = Manager->BoxesNum - 3;

				if (ClickSound && RemoveSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), RemoveSound, this->GetActorLocation());
				}
				UE_LOG(LogTemp, Display, TEXT("Sort Type"));
				Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 10; });
				//顺子消除加分


				//判断是否通关
				if (Manager->BoxesNum == 0)
				{
					Manager->IsSuc = true;
					//OwningManager->ShowWinWBP();
					//UGameplaystatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);
					UGameplayStatics::OpenLevel(GetWorld(), Level);
				}
			}
			else
			{

				for (auto Box : BoxArray) {
					//将三个盒子去除高亮
					//Box->BlockMesh->SetRenderCustomDepth(false);
					Box->BlockMesh->SetMaterial(0, BaseMaterial);
					
					Box->bIsActive = false;
				}
				Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 10; });
				UE_LOG(LogTemp, Display, TEXT("RemoveAll_1"));
			}
		}
		else
		{
			for (auto Box : BoxArray) {
				//将三个盒子去除高亮
				//Box->BlockMesh->SetRenderCustomDepth(false);
				Box->BlockMesh->SetMaterial(0, BaseMaterial);
				Box->bIsActive = false;
			}
			Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 10; });
			UE_LOG(LogTemp, Display, TEXT("RemoveAll_2"));
		}

	}

}

template <typename T1>
void ANoteBookBlock::HandleSameBoxArray(T1 Manager, ANoteBookBlock* self, FName Level)
{
	if (!self) return;

	Manager->Boxes.Add(self);
	auto BoxArray = Manager->Boxes;

	if (BoxArray.Num() == 3)
	{
		UE_LOG(LogTemp, Display, TEXT("%i"), BoxArray.Num());

		if (BoxArray[0] == nullptr && BoxArray[1] == nullptr && BoxArray[2] == nullptr)
		{
			Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 100; });
			UE_LOG(LogTemp, Display, TEXT("nullptr"));
			return;
		};

		if (BoxArray[0]->BoxInfo.Type == BoxArray[1]->BoxInfo.Type && BoxArray[1]->BoxInfo.Type == BoxArray[2]->BoxInfo.Type)
		{

			if (BoxArray[0]->BoxInfo.TypeNum == BoxArray[1]->BoxInfo.TypeNum &&
				BoxArray[2]->BoxInfo.TypeNum == BoxArray[1]->BoxInfo.TypeNum)
			{
				for (auto Box : BoxArray) {
					//消除选中的盒子
					GetWorld()->DestroyActor(Box, false, false);
					OnBoxesDelete.Broadcast();
				}
				Manager->BoxesNum = Manager->BoxesNum - 3;

				if (ClickSound && RemoveSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), RemoveSound, this->GetActorLocation());
				}
				UE_LOG(LogTemp, Display, TEXT("Same Box"));
				Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 100; });
				//相同消除加分


				//判断是否通关
				if (Manager->BoxesNum == 0)
				{
					Manager->IsSuc = true;
					//OwningManager->ShowWinWBP();
					//UGameplaystatics::LoadStreamLevel(this,LevelToLoad,true,true, LatentInfo);
					UGameplayStatics::OpenLevel(GetWorld(), Level);
				}
			}
			else
			{
				for (auto Box : BoxArray) {
					//将三个盒子去除高亮
					//Box->BlockMesh->SetRenderCustomDepth(false);
					Box->BlockMesh->SetMaterial(0, BaseMaterial);

					Box->bIsActive = false;
				}
				Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 100; });

			}
		}
		else
		{
			for (auto Box : BoxArray) {
				//将三个盒子去除高亮
				//Box->BlockMesh->SetRenderCustomDepth(false);
				Box->BlockMesh->SetMaterial(0, BaseMaterial);
				Box->bIsActive = false;
			}
			Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 100; });

		}

	}

}

void ANoteBookBlock::GetCurrentBoxNums(int32 Nums)
{

}

void ANoteBookBlock::AddScore(int32 Nums)
{

}