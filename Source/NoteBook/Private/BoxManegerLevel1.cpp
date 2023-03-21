// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxManegerLevel1.h"
#include "NoteBook/NoteBookBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABoxManegerLevel1::ABoxManegerLevel1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/************************加载方块贴图*************************/
	struct FConstructorStatics2
	{
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>   OneTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	TwoTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	ThreeTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FourTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FiveTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	SixTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	SevenTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	EightTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	NineTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	ShiTong;

		FConstructorStatics2() :
			OneTong(TEXT("/Game/Texture/Level1_Box/10.10"))
			, TwoTong(TEXT("/Game/Texture/Level1_Box/2.2"))
			, ThreeTong(TEXT("/Game/Texture/Level1_Box/3.3"))
			, FourTong(TEXT("/Game/Texture/Level1_Box/4.4"))
			, FiveTong(TEXT("/Game/Texture/Level1_Box/5.5"))
			, SixTong(TEXT("/Game/Texture/Level1_Box/6.6"))
			, SevenTong(TEXT("/Game/Texture/Level1_Box/7.7"))
			, EightTong(TEXT("/Game/Texture/Level1_Box/8.8"))
			, NineTong(TEXT("/Game/Texture/Level1_Box/9.9"))
			, ShiTong(TEXT("/Game/Texture/Level1_Box/1.1"))
		{
		}

	};
	static FConstructorStatics2 ConstructorStatics2;

	/************************方块贴图储存为数组*************************/

	TexArray.Emplace(ConstructorStatics2.OneTong.Get());
	TexArray.Emplace(ConstructorStatics2.TwoTong.Get());
	TexArray.Emplace(ConstructorStatics2.ThreeTong.Get());
	TexArray.Emplace(ConstructorStatics2.FourTong.Get());
	TexArray.Emplace(ConstructorStatics2.FiveTong.Get());
	TexArray.Emplace(ConstructorStatics2.SixTong.Get());
	TexArray.Emplace(ConstructorStatics2.SevenTong.Get());
	TexArray.Emplace(ConstructorStatics2.EightTong.Get());
	TexArray.Emplace(ConstructorStatics2.NineTong.Get());
	TexArray.Emplace(ConstructorStatics2.ShiTong.Get());

	for (int i = 0; i < 10; i++) {

		F_NumPair S_NumPair{ "TongZi",i + 1 ,TexArray[i],nullptr };
		BoxesMap.Add(i, S_NumPair);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::FromInt(Band));
		//UE_LOG(LogTemp, Display, TEXT("value:%s"), *FString::FromInt(Band));

	}


}

// Called when the game starts or when spawned
void ABoxManegerLevel1::BeginPlay()
{
	Super::BeginPlay();
	
	SetBoxTexture(OutActors, BoxesMap);
}

void ABoxManegerLevel1::SetBoxTexture(TArray<AActor*> Actors, TMap<int32, F_NumPair> Map)
{
	/************************获取场景中方块*************************/
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANoteBookBlock::StaticClass(), Actors);

	BoxesNum = Actors.Num();
	//UE_LOG(LogTemp, Display, TEXT("%i"), BoxesNum);

	//随机排序
	Actors.Sort([](const AActor& A, const AActor& B) {
		return  FMath::RandRange(0, 10) > FMath::RandRange(0, 10);
		});

	int i = 0;
	for (auto Box : Actors)
	{
		if (Box) {
			ANoteBookBlock* TempBookBlock = Cast<ANoteBookBlock>(Box);
			auto DynMaterial = TempBookBlock->GetBlockMesh()->CreateDynamicMaterialInstance(1);
			DynMaterial->SetTextureParameterValue("Texture", TexArray[i % 10]);

			TempBookBlock->BoxInfo.Type = BoxesMap.Find(i % 10)->Type;
			TempBookBlock->BoxInfo.TypeNum = BoxesMap.Find(i % 10)->TypeNum;
			TempBookBlock->BoxInfo.Texture = BoxesMap.Find(i % 10)->Texture;

			TempBookBlock->OwningManagerLevel1 = this;//设置Box的管理者

			//UE_LOG(LogTemp, Display, TEXT("%i"), Actors.Num());
		}
		i++;
	}


}



