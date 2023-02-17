// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("LookUp", this, &AMyPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AMyPawn::AddControllerYawInput);
}

