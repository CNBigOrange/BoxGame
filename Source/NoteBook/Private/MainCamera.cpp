// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainCamera::AMainCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	//SpringArm->SetupAttachment(Root);
	//SpringArm->bUsePawnControlRotation = true;
	//SpringArm->SocketOffset = FVector(0.f, 0.f, 0.f);

	//Camera1 = CreateDefaultSubobject<UCameraComponent>("Camera1");

	//Camera1->SetupAttachment(SpringArm);


	//Camera1->AddRelativeLocation(FVector(0.f,0.f,0.f));
}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

