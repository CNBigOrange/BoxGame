// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoteBookBlock.h"
#include "NoteBookBlockGrid.h"
#include "UObject/ConstructorHelpers.h"//加载资源方式，ConstructorHelpers只能在构造函数中使用。
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"
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
			, BaseMaterial(TEXT("/Game/Geometry/Meshes/Box/Material_004.Material_004"))
			, TextureMaterial(TEXT("/Game/Geometry/Meshes/Box/Material_002_Inst.Material_002_Inst"))
			, CheckedMaterial(TEXT("/Game/Geometry/Meshes/Box/M_CheckedMaterial_Inst.M_CheckedMaterial_Inst"))
			, ClickSoundInst(TEXT("/Game/Music/ClickSound.ClickSound"))
			, RemoveSoundInst(TEXT("/Game/Music/RemoveSound.RemoveSound"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	/*DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	DummyRoot->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	SceneC = CreateDefaultSubobject<USceneComponent>(TEXT("SceneC"));
	RootComponent = DummyRoot;
	SceneC->SetupAttachment(RootComponent);*/

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.1f,0.1f,0.1f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,10.f));
	BlockMesh->SetRelativeRotation(FRotator(0.f, 0.f, 180.f));//FRotator
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	BlockMesh->SetMaterial(1, ConstructorStatics.TextureMaterial.Get());
	//BlockMesh->OnClicked.AddDynamic(this, &ANoteBookBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ANoteBookBlock::OnFingerPressedBlock);
	BlockMesh->SetRenderCustomDepth(false);
	BlockMesh->SetSimulatePhysics(false);

	//Create boxCollision component
	/*BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BoxCollision->SetBoxExtent(FVector(9.f, 9.f, 9.f));
	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));*/

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

		//点击事件
		OnClickBox.Broadcast();

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

		//第二关
		if (OwningManagerLevel2) {
			HandleSameBoxArray3<ABoxManegerLevel2*>(OwningManagerLevel2, this , "Level3");
			//UE_LOG(LogTemp,Display,TEXT(""))
		}
		//第一关
		else if (OwningManagerLevel1) {
			HandleSameBoxArray3<ABoxManegerLevel1*>(OwningManagerLevel1, this , "Level2");
		}
		//第三关
		else if (OwningManagerLevel3) {
			HandleSameBoxArray3<ABaseBoxManegerLevel3*>(OwningManagerLevel3, this, "Level_4");
		}
		//第四关
		else if (OwningManager) {
			HandleBoxArray<ABoxManeger*>(OwningManager, this, "Level_5");
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

	if (BoxArray.Num() == 2)
	{
		if (BoxArray[0] == nullptr && BoxArray[1] == nullptr)
		{
			Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 10; });
			UE_LOG(LogTemp, Display, TEXT("nullptr"));
			return;
		}
		if (BoxArray[0]->BoxInfo.Type != BoxArray[1]->BoxInfo.Type)
		{
			BoxArray[0]->BlockMesh->SetMaterial(0, BaseMaterial);

			BoxArray[0]->bIsActive = false;
			Manager->Boxes.RemoveAt(0);
		}
		else if (BoxArray[0]->BoxInfo.TypeNum != BoxArray[1]->BoxInfo.TypeNum)
		{
			BoxArray[0]->BlockMesh->SetMaterial(0, BaseMaterial);

			BoxArray[0]->bIsActive = false;
			Manager->Boxes.RemoveAt(0);
		}
	}


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
void ANoteBookBlock::HandleSameBoxArray3(T1 Manager, ANoteBookBlock* self, FName Level)
{
	if (!self) return;

	Manager->Boxes.Add(self);
	auto BoxArray = Manager->Boxes;

	if (BoxArray.Num() == 2)
	{
		if (BoxArray[0] == nullptr && BoxArray[1] == nullptr)
		{
			Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 10; });
			UE_LOG(LogTemp, Display, TEXT("nullptr"));
			return;
		}
		if (BoxArray[0]->BoxInfo.Type != BoxArray[1]->BoxInfo.Type)
		{
			BoxArray[0]->BlockMesh->SetMaterial(0, BaseMaterial);

			BoxArray[0]->bIsActive = false;
			Manager->Boxes.RemoveAt(0);
		}
		else if (BoxArray[0]->BoxInfo.TypeNum != BoxArray[1]->BoxInfo.TypeNum)
		{
			BoxArray[0]->BlockMesh->SetMaterial(0, BaseMaterial);

			BoxArray[0]->bIsActive = false;
			Manager->Boxes.RemoveAt(0);
		}
	}

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

template <typename T1>
void ANoteBookBlock::HandleSameBoxArray2(T1 Manager, ANoteBookBlock* self, FName Level)
{
	if (!self) return;

	Manager->Boxes.Add(self);
	auto BoxArray = Manager->Boxes;
	
	if (BoxArray.Num() == 2)
	{
		UE_LOG(LogTemp, Display, TEXT("%i"), BoxArray.Num());

		if (BoxArray[0] == nullptr && BoxArray[1] == nullptr)
		{
			Manager->Boxes.RemoveAll([](ANoteBookBlock* C) {return C->BoxInfo.TypeNum < 100; });
			UE_LOG(LogTemp, Display, TEXT("nullptr"));
			return;
		};

		if (BoxArray[0]->BoxInfo.Type == BoxArray[1]->BoxInfo.Type)
		{

			if (BoxArray[0]->BoxInfo.TypeNum == BoxArray[1]->BoxInfo.TypeNum)
			{
				for (auto Box : BoxArray) {
					//消除选中的盒子
					GetWorld()->DestroyActor(Box, false, false);
					OnBoxesDelete.Broadcast();
				}
				Manager->BoxesNum = Manager->BoxesNum - 2;

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