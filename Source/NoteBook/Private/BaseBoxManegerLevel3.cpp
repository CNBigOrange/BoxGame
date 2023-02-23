// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBoxManegerLevel3.h"
#include "NoteBook/NoteBookBlock.h"
#include "Kismet/GameplayStatics.h"

ABaseBoxManegerLevel3::ABaseBoxManegerLevel3()
{
	//Super::ABaseBoxManeger();

	/************************加载方块贴图*************************/
	struct FConstructorStatics3
	{
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>   OneTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	TwoTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	ThreeTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FourTong;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FiveTong;


		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	OneWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	TwoWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	ThreeWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FourWan;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	FiveWan;

		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	OneTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	TwoTiao;
		ConstructorHelpers::FObjectFinderOptional<UTexture2D>	ThreeTiao;
		FConstructorStatics3() :
			OneTong(TEXT("/Game/Texture/Level2_Box/1Tong.1Tong"))
			, TwoTong(TEXT("/Game/Texture/Level2_Box/2Tong.2Tong"))
			, ThreeTong(TEXT("/Game/Texture/Level2_Box/3Tong.3Tong"))
			, FourTong(TEXT("/Game/Texture/Level2_Box/4Tong.4Tong"))
			, FiveTong(TEXT("/Game/Texture/Level2_Box/5Tong.5Tong"))


			, OneWan(TEXT("/Game/Texture/Level2_Box/1wan.1wan"))
			, TwoWan(TEXT("/Game/Texture/Level2_Box/2wan.2wan"))
			, ThreeWan(TEXT("/Game/Texture/Level2_Box/3wan.3wan"))
			, FourWan(TEXT("/Game/Texture/Level2_Box/4wan.4wan"))
			, FiveWan(TEXT("/Game/Texture/Level2_Box/5wan.5wan"))


			, OneTiao(TEXT("/Game/Texture/Level2_Box/1tiao.1tiao"))
			, TwoTiao(TEXT("/Game/Texture/Level2_Box/2tiao.2tiao"))
			, ThreeTiao(TEXT("/Game/Texture/Level2_Box/3tiao.3tiao"))
		{
		}

	};
	static FConstructorStatics3 ConstructorStatics3;

	/************************方块贴图储存为数组*************************/

	TexArray.Emplace(ConstructorStatics3.OneTong.Get());
	TexArray.Emplace(ConstructorStatics3.TwoTong.Get());
	TexArray.Emplace(ConstructorStatics3.ThreeTong.Get());
	TexArray.Emplace(ConstructorStatics3.FourTong.Get());
	TexArray.Emplace(ConstructorStatics3.FiveTong.Get());


	TexArray.Emplace(ConstructorStatics3.OneWan.Get());
	TexArray.Emplace(ConstructorStatics3.TwoWan.Get());
	TexArray.Emplace(ConstructorStatics3.ThreeWan.Get());
	TexArray.Emplace(ConstructorStatics3.FourWan.Get());
	TexArray.Emplace(ConstructorStatics3.FiveWan.Get());


	TexArray.Emplace(ConstructorStatics3.OneTiao.Get());
	TexArray.Emplace(ConstructorStatics3.TwoTiao.Get());
	TexArray.Emplace(ConstructorStatics3.ThreeTiao.Get());

	for (int i = 0; i < 13; i++) {

		F_NumPair S_NumPair{ "TongZi",i ,TexArray[i],nullptr };
		BoxesMap.Add(i, S_NumPair);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::FromInt(Band));
		//UE_LOG(LogTemp, Display, TEXT("value:%s"), *FString::FromInt(Band));

	}

}

void ABaseBoxManegerLevel3::BeginPlay()
{
	Super::BeginPlay();

	SetBoxTexture(OutActors, BoxesMap);
}

void ABaseBoxManegerLevel3::SetBoxTexture(TArray<AActor*> Actors, TMap<int32, F_NumPair> Map)
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
			DynMaterial->SetTextureParameterValue("Texture", TexArray[i % 13]);

			TempBookBlock->BoxInfo.Type = BoxesMap.Find(i % 13)->Type;
			TempBookBlock->BoxInfo.TypeNum = BoxesMap.Find(i % 13)->TypeNum;
			TempBookBlock->BoxInfo.Texture = BoxesMap.Find(i % 13)->Texture;

			TempBookBlock->OwningManagerLevel3 = this;//设置Box的管理者

			//UE_LOG(LogTemp, Display, TEXT("%i"), Actors.Num());
		}
		i++;
	}

}
