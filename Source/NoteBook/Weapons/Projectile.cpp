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
	//ECollisionEnabled::QueryOnly��ʾ����ѯ��ײ��������������������ECollisionEnabled::QueryAndPhysics��ʾ�Ȳ�ѯ���������������
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//������ײ��Ӧ������ͨ��������Ҳ�������ò�ͬͨ��������ͬ����ײ��Ӧ
	SetRootComponent(CollisionComponent);//���ø�����

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");//��ʼ�����������
	MovementComponent->InitialSpeed = 500.0f;//�ٶȴ�С
	MovementComponent->ProjectileGravityScale = 0.0f;//������С
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	check(MovementComponent);//���ָ���Ƿ�Ϊ��
	check(CollisionComponent);

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

	//�����ٶ� = ShotDirection������λ������ ���Գ�ʶ���ٶȣ�����Velocity��һ��FVector
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
	//OnComponentHit�Ƕ�̬ί�У�����ײ������Դ���ί�У���Begin�󶨶�̬ί��

	SetLifeSpan(LifeSeconds);//ͨ����ʱ����������ʱ�䣬��ֹ�ӵ�̫�ർ���ڴ������
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
					 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld())return;

	//MovementComponent->StopMovementImmediately();
	//Destroy();
}

