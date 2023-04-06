// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBoxManeger.h"
#include "NoteBook/NoteBookBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABaseBoxManeger::ABaseBoxManeger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;


}

// Called when the game starts or when spawned
void ABaseBoxManeger::BeginPlay()
{
	Super::BeginPlay();
	
	//GetWorldTimerManager().SetTimer(TimeHandle, this, &ABaseBoxManeger::CreateSaveGameObj, 2.0f, false, 1.0f);
}

UMySaveGame* ABaseBoxManeger::CreateSaveGameObj()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	
	return SaveGameInstance;
}