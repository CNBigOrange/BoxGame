// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBoxManeger.h"
#include "BaseBoxManegerLevel3.generated.h"

/**
 * 
 */
UCLASS()
class NOTEBOOK_API ABaseBoxManegerLevel3 : public ABaseBoxManeger
{
	GENERATED_BODY()
	
		ABaseBoxManegerLevel3();


protected:

	UFUNCTION()
		virtual void SetBoxTexture(TArray<AActor*> Actors, TMap<int32, F_NumPair> Map) override;

	virtual void BeginPlay() override;
};
