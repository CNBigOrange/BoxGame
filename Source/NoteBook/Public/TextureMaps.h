#pragma once
#include "Materials/MaterialInstance.h"
//#include "..\Materials\MaterialInstanceDynamic.h"
#include "TextureMaps.generated.h"

class ANoteBookBlock;//前置声明，取代包含头文件，防止循环依赖

USTRUCT(BlueprintType)
struct F_NumPair {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
		FString Type = "";
	UPROPERTY(BlueprintReadWrite)
		int32 TypeNum = 0;
	UPROPERTY(BlueprintReadWrite)
		UTexture2D* Texture = nullptr;
	UPROPERTY(BlueprintReadWrite)
		UMaterialInstanceDynamic* BookBlockMaterial = nullptr;
};

UENUM(BlueprintType)
enum class EBoxName :uint8
{
	yitong = 0,
	ertong,
	santong,
	sitong,
	wutong,
	liutong,
	qitong,
	batong,
	jiutong,

	yiwan,
	erwan,
	sanwan,
	siwan,
	wuwan,
	liuwan,
	qiwan,
	bawan,
	jiuwan,

	yitiao,
	ertiao,
	santiao,
	sitiao,
	wutiao,
	liutiao,
	qitiao,
	batiao,
	jiutiao,
};


