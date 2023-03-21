// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"//尼亚加拉函数库
#include "NiagaraComponent.h"//尼亚加拉组件
#include "MyPlayerController.h"
#include "NoteBook/Weapons/Projectile.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());//设置附着

	//NS_TraceLine = CreateDefaultSubobject<UNiagaraSystem>("NS_TraceLine");
	//NS_TraceLine->SetupAttachment(WeaponMesh);


	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	
	//Root = CreateDefaultSubobject<USceneComponent>("Root");
	//RootComponent = Root;
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

	//SpringArm->SetupAttachment(Root);
	//SpringArm->bUsePawnControlRotation = true;
	////SpringArm->SocketOffset = FVector(0.f, 0.f, 0.f);

	//Camera1 = CreateDefaultSubobject<UCameraComponent>("Camera1");

	//Camera1->SetupAttachment(SpringArm);

	//Camera1->AddRelativeLocation(FVector(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AMyPawn::BindOnClikEvent()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANoteBookBlock::StaticClass(), Actors);
	for (auto One : Actors)
	{
		Box = Cast< ANoteBookBlock>(One);
		Box->OnClickBox.AddDynamic(this, &AMyPawn::MakeShot);
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("LookUp", this, &AMyPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AMyPawn::AddControllerYawInput);
}

void AMyPawn::MakeShot()
{
	FVector Direction = WeaponMesh->GetForwardVector();
	const FTransform spawntransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AProjectile* projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, spawntransform);
	//延迟开始生成抛射物
	if (projectile)
	{
		projectile->SetShotDirection(Direction);
		projectile->SetOwner(GetOwner());//设置拥有者
		projectile->FinishSpawning(spawntransform);//完成生成
	}
}


FVector AMyPawn::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}
