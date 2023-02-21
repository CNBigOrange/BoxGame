// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TextureMaps.h"
#include "Math/UnrealMathUtility.h"
#include "BaseBoxManeger.generated.h"

UCLASS()
class NOTEBOOK_API ABaseBoxManeger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBoxManeger();

	UPROPERTY()
		TArray<AActor*> OutActors;

	UPROPERTY()
		int32 BoxesNum;

	UPROPERTY()
		TMap<int32, F_NumPair> BoxesMap;

	UPROPERTY()
		TArray<UTexture2D*> TexArray;

	UPROPERTY()
		TArray<ANoteBookBlock*> Boxes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsSuc = false;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UUserWidget* WBP_Suc;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetBoxTexture(TArray<AActor*> Actors, TMap<int32, F_NumPair> Map) {};

};
