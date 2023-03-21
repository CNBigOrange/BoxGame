// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class NOTEBOOK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		USphereComponent* CollisionComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UProjectileMovementComponent* MovementComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float LifeSeconds = 4.0f;

private:
	FVector ShotDirection;

	UFUNCTION(BlueprintCallable)
		void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
							 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetControlller() const;
};
