// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoxGameSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "NoteBook/NoteBookBlock.h"

void UMyBoxGameSubsystem::Initi()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANoteBookBlock::StaticClass(), Actors);

	BoxNums = Actors.Num();
	Score = 0;
	for (auto One : Actors)
	{
		Box = Cast< ANoteBookBlock>(One);
		Box->OnBoxesDelete.AddDynamic(this,&UMyBoxGameSubsystem::SetCurrentBoxNums);
		Box->OnBoxesDelete.AddDynamic(this, &UMyBoxGameSubsystem::AddScore);
	}

}

void UMyBoxGameSubsystem::SetCurrentBoxNums()
{
	BoxNums -= 1;
}

void UMyBoxGameSubsystem::AddScore()
{
	Score += 5;
}

void UMyBoxGameSubsystem::SaveGameData(int current_level)
{
	if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>
		(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
	{
		SaveGameInstance->Level = current_level;

		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	}
}

const int& UMyBoxGameSubsystem::LoadingGameData()
{
	//…Ë÷√ŒØÕ–
	//FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	if (UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameSaveSlot"), 0)))
	{
		return LoadedGame->Level;
	}
	return  i;
}