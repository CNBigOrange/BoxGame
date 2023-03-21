// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteBook/Weapons/Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(1.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//ECollisionEnabled::QueryOnly表示仅查询碰撞结果，不会产生物理交互，ECollisionEnabled::QueryAndPhysics表示既查询结果还发生物理交互
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//设置碰撞反应对所有通道产生，也可以设置不同通道产生不同的碰撞反应
	SetRootComponent(CollisionComponent);//设置根主件

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");//初始化发射物组件
	MovementComponent->InitialSpeed = 500.0f;//速度大小
	MovementComponent->ProjectileGravityScale = 0.0f;//重力大小
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	check(MovementComponent);//检查指针是否为空
	check(CollisionComponent);

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

	//设置速度 = ShotDirection（方向单位向量） 乘以初识化速度，这里Velocity是一个FVector
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
	//OnComponentHit是动态委托，是碰撞组件内自带的委托，在Begin绑定动态委托

	SetLifeSpan(LifeSeconds);//通过计时器设置声明时间，防止子弹太多导致内存的消耗
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
					 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld())return;

	//MovementComponent->StopMovementImmediately();
	//Destroy();
}

