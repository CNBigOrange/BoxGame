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

		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	OneWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	TwoWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	ThreeWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FourWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FiveWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	SixWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	SevenWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	EightWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	NineWan;

		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	OneTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	TwoTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	ThreeTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FourTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FiveTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	SixTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	SevenTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	EightTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	NineTiao;

		FConstructorStatics2() :
			OneTong(TEXT("/Game/Texture/Level2_Box/1Tong.1Tong"))
			, TwoTong(TEXT("/Game/Texture/Level2_Box/2Tong.2Tong"))
			, ThreeTong(TEXT("/Game/Texture/Level2_Box/3Tong.3Tong"))
			, FourTong(TEXT("/Game/Texture/Level2_Box/4Tong.4Tong"))
			, FiveTong(TEXT("/Game/Texture/Level2_Box/5Tong.5Tong"))
			, SixTong(TEXT("/Game/Texture/Level2_Box/6Tong.6Tong"))
			, SevenTong(TEXT("/Game/Texture/Level2_Box/7Tong.7Tong"))
			, EightTong(TEXT("/Game/Texture/Level2_Box/8Tong.8Tong"))
			, NineTong(TEXT("/Game/Texture/Level2_Box/9Tong.9Tong"))

			, OneWan(TEXT("/Game/Texture/Level2_Box/1wan.1wan"))
			, TwoWan(TEXT("/Game/Texture/Level2_Box/2wan.2wan"))
			, ThreeWan(TEXT("/Game/Texture/Level2_Box/3wan.3wan"))
			, FourWan(TEXT("/Game/Texture/Level2_Box/4wan.4wan"))
			, FiveWan(TEXT("/Game/Texture/Level2_Box/5wan.5wan"))
			, SixWan(TEXT("/Game/Texture/Level2_Box/6wan.6wan"))
			, SevenWan(TEXT("/Game/Texture/Level2_Box/7wan.7wan"))
			, EightWan(TEXT("/Game/Texture/Level2_Box/8wan.8wan"))
			, NineWan(TEXT("/Game/Texture/Level2_Box/9wan.9wan"))

			, OneTiao(TEXT("/Game/Texture/Level2_Box/1tiao.1tiao"))
			, TwoTiao(TEXT("/Game/Texture/Level2_Box/2tiao.2tiao"))
			, ThreeTiao(TEXT("/Game/Texture/Level2_Box/3tiao.3tiao"))
			, FourTiao(TEXT("/Game/Texture/Level2_Box/4tiao.4tiao"))
			, FiveTiao(TEXT("/Game/Texture/Level2_Box/5tiao.5tiao"))
			, SixTiao(TEXT("/Game/Texture/Level2_Box/6tiao.6tiao"))
			, SevenTiao(TEXT("/Game/Texture/Level2_Box/7tiao.7tiao"))
			, EightTiao(TEXT("/Game/Texture/Level2_Box/8tiao.8tiao"))
			, NineTiao(TEXT("/Game/Texture/Level2_Box/9tiao.9tiao"))
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

	TexArray.Emplace(ConstructorStatics2.OneWan.Get());
	TexArray.Emplace(ConstructorStatics2.TwoWan.Get());
	TexArray.Emplace(ConstructorStatics2.ThreeWan.Get());
	TexArray.Emplace(ConstructorStatics2.FourWan.Get());
	TexArray.Emplace(ConstructorStatics2.FiveWan.Get());
	TexArray.Emplace(ConstructorStatics2.SixWan.Get());
	TexArray.Emplace(ConstructorStatics2.SevenWan.Get());
	TexArray.Emplace(ConstructorStatics2.EightWan.Get());
	TexArray.Emplace(ConstructorStatics2.NineWan.Get());

	TexArray.Emplace(ConstructorStatics2.OneTiao.Get());
	TexArray.Emplace(ConstructorStatics2.TwoTiao.Get());
	TexArray.Emplace(ConstructorStatics2.ThreeTiao.Get());
	TexArray.Emplace(ConstructorStatics2.FourTiao.Get());
	TexArray.Emplace(ConstructorStatics2.FiveTiao.Get());
	TexArray.Emplace(ConstructorStatics2.SixTiao.Get());
	TexArray.Emplace(ConstructorStatics2.SevenTiao.Get());
	TexArray.Emplace(ConstructorStatics2.EightTiao.Get());
	TexArray.Emplace(ConstructorStatics2.NineTiao.Get());

	for (int i = 0; i < 9; i++) {

		F_NumPair S_NumPair{ "TongZi",i + 1 ,TexArray[i],nullptr };
		BoxesMap.Add(i, S_NumPair);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::FromInt(Band));
		//UE_LOG(LogTemp, Display, TEXT("value:%s"), *FString::FromInt(Band));

		S_NumPair.Type = "Wan";
		S_NumPair.Texture = TexArray[i + 9];
		BoxesMap.Add(i + 9, S_NumPair);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::FromInt(Band));
		//UE_LOG(LogTemp, Display, TEXT("value:%s"), *FString::FromInt(Band));

		S_NumPair.Type = "TiaoZi";
		S_NumPair.Texture = TexArray[i + 18];
		BoxesMap.Add(i + 18, S_NumPair);
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
	UE_LOG(LogTemp, Display, TEXT("%i"), BoxesNum);

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
			DynMaterial->SetTextureParameterValue("Texture", TexArray[i % 27]);

			TempBookBlock->BoxInfo.Type = BoxesMap.Find(i % 27)->Type;
			TempBookBlock->BoxInfo.TypeNum = BoxesMap.Find(i % 27)->TypeNum;
			TempBookBlock->BoxInfo.Texture = BoxesMap.Find(i % 27)->Texture;

			TempBookBlock->OwningManager = this;//设置Box的管理者

			//UE_LOG(LogTemp, Display, TEXT("%i"), Actors.Num());
		}
		i++;
	}


}



