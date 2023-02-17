// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TextureMaps.h"
#include "BoxManeger.generated.h"


class ANoteBookBlock;
UCLASS()
class NOTEBOOK_API ABoxManeger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxManeger();

	UPROPERTY()
	TArray<AActor*> OutActors;

	UPROPERTY()
	TMap<int32, F_NumPair> BoxesMap;

	UPROPERTY()
	TArray<UTexture2D*> TexArray;

	UPROPERTY()
	TArray<ANoteBookBlock*> Boxes;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsSuc = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetBoxTexture(TArray<AActor*> Actors, TMap<int32, F_NumPair> Map);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
