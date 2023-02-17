// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainCamera.generated.h"

class UCameraComponent;//Ç°ÖÃÉùÃ÷
class USpringArmComponent;

UCLASS()
class NOTEBOOK_API AMainCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainCamera();

	UPROPERTY(Category = Camera, VisibleAnywhere,BlueprintReadWrite)
	UCameraComponent* Camera1;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(Category = Center, VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
