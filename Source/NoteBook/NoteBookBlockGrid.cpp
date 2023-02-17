// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoteBookBlockGrid.h"
#include "NoteBookBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ANoteBookBlockGrid::ANoteBookBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	DummyRoot2 = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy1"));
	DummyRoot2->SetupAttachment(DummyRoot);

	// Create static mesh component
	//ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	//ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	//ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	//ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	//ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	XSize = 3;
	ZSize = 3;
	YSize = 3;
	BlockSpacing = 20.f;
}


void ANoteBookBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = XSize;


	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex % XSize) * BlockSpacing; // Divide by dimension
		
		const FVector BlockLocation = FVector(XOffset, 0, 0) + GetActorLocation();

		// Spawn a block
		ANoteBookBlock* NewBlock = GetWorld()->SpawnActor<ANoteBookBlock>(BlockLocation, FRotator(0, 0, 0));
		SetBlockOwner(NewBlock);

		for (int32 YBlockIndex = 1; YBlockIndex < YSize; YBlockIndex++)
		{
			const float YOffset = (YBlockIndex % YSize) * BlockSpacing; // Modulo gives remainder
			const FVector YBlockLocation = FVector(XOffset, YOffset, 0) + GetActorLocation();
			// Spawn a block
			ANoteBookBlock* YNewBlock = GetWorld()->SpawnActor<ANoteBookBlock>(YBlockLocation, FRotator(0, 0, 0));

			SetBlockOwner(YNewBlock);

			for (int32 ZBlockIndex = 1; ZBlockIndex < ZSize; ZBlockIndex++)
			{
				const float ZOffset = (ZBlockIndex % ZSize) * BlockSpacing;

				const FVector ZBlockLocation = FVector(XOffset, YOffset, ZOffset) + GetActorLocation();

				ANoteBookBlock* ZNewBlock = GetWorld()->SpawnActor<ANoteBookBlock>(ZBlockLocation, FRotator(0, 0, 0));

				SetBlockOwner(ZNewBlock);
			}
		}

		for (int32 ZBlockIndex = 1; ZBlockIndex < ZSize; ZBlockIndex++)
		{
			const float ZOffset = (ZBlockIndex % ZSize) * BlockSpacing;

			const FVector ZBlockLocation = FVector(XOffset, 0, ZOffset) + GetActorLocation();

			ANoteBookBlock* ZNewBlock = GetWorld()->SpawnActor<ANoteBookBlock>(ZBlockLocation, FRotator(0, 0, 0));

			SetBlockOwner(ZNewBlock);
		}
	}

	GetWorld()->SpawnActor<ABoxManeger>(FVector(0,0,0),FRotator(0,0,0));//在Box生成后创建管理类
}


void ANoteBookBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	//ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

bool ANoteBookBlockGrid::SetBlockOwner(ANoteBookBlock* NewBlock)
{
	bool SetSuc{ false };
	// Tell the block about its owner告诉Block的拥有者
	if (NewBlock != nullptr)
	{
		NewBlock->OwningGrid = this;//给ANoteBookBlock对象内部的ANoteBookBlockGrid变量赋值为当前实例
		SetSuc = true;
	}
	return SetSuc;
}

#undef LOCTEXT_NAMESPACE
