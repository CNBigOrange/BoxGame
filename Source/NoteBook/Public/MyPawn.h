// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCameraComponent;//Ç°ÖÃÉùÃ÷
class USpringArmComponent;

UCLASS()
class NOTEBOOK_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
		UCameraComponent* Camera1;

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;

	UPROPERTY(Category = Center, EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
