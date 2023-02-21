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
	
}
