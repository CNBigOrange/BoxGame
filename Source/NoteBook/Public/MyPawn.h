// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NoteBook/NoteBookBlock.h"
#include "MyPawn.generated.h"

class UCameraComponent;//ǰ������
class USpringArmComponent;
class USkeletalMeshComponent;//����������
class UNiagaraSystem;
class UNiagaraComponent;
class AProjectile;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;//����������
	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, Category = "Components")
		ANoteBookBlock* Box;
	//UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, Category = "Components")
	//	UNiagaraSystem* NS_TraceLine;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FName MuzzleSocketName = "MuzzleSocket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float TraceMaxDistance = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		UNiagaraSystem* MuzzleFX;//����ǹ����Ч

	UFUNCTION(BlueprintCallable)
		void MakeShot();

	FVector GetMuzzleWorldLocation() const;

	UNiagaraComponent* SpawnMuzzleFX();//����ǹ����Ч����

	UFUNCTION(BlueprintCallable)
	void BindOnClikEvent();
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
