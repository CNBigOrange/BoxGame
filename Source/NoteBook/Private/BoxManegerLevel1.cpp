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

		FConstructorStatics2() :
			OneTong(TEXT("/Game/Texture/Level2_Box/1tong.1tong"))
			, TwoTong(TEXT("/Game/Texture/Level2_Box/2tiao.2tiao"))
			, ThreeTong(TEXT("/Game/Texture/Level2_Box/3wan.3wan"))
			, FourTong(TEXT("/Game/Texture/Level2_Box/4tong.4tong"))
			, FiveTong(TEXT("/Game/Texture/Level2_Box/5tiao.5tiao"))
			, SixTong(TEXT("/Game/Texture/Level2_Box/6wan.6wan"))
			, SevenTong(TEXT("/Game/Texture/Level2_Box/7tiao.7tiao"))
			, EightTong(TEXT("/Game/Texture/Level2_Box/8tong.8tong"))
			, NineTong(TEXT("/Game/Texture/Level2_Box/9wan.9wan"))
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

	for (int i = 0; i < 9; i++) {

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
			DynMaterial->SetTextureParameterValue("Texture", TexArray[i % 9]);

			TempBookBlock->BoxInfo.Type = BoxesMap.Find(i % 9)->Type;
			TempBookBlock->BoxInfo.TypeNum = BoxesMap.Find(i % 9)->TypeNum;
			TempBookBlock->BoxInfo.Texture = BoxesMap.Find(i % 9)->Texture;

			TempBookBlock->OwningManagerLevel1 = this;//设置Box的管理者

			//UE_LOG(LogTemp, Display, TEXT("%i"), Actors.Num());
		}
		i++;
	}


}



