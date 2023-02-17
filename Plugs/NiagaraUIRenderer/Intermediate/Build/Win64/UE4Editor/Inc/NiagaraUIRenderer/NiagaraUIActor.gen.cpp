// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NiagaraUIRenderer/Public/NiagaraUIActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNiagaraUIActor() {}
// Cross Module References
	NIAGARAUIRENDERER_API UClass* Z_Construct_UClass_ANiagaraUIActor_NoRegister();
	NIAGARAUIRENDERER_API UClass* Z_Construct_UClass_ANiagaraUIActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_NiagaraUIRenderer();
// End Cross Module References
	void ANiagaraUIActor::StaticRegisterNativesANiagaraUIActor()
	{
	}
	UClass* Z_Construct_UClass_ANiagaraUIActor_NoRegister()
	{
		return ANiagaraUIActor::StaticClass();
	}
	struct Z_Construct_UClass_ANiagaraUIActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ANiagaraUIActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_NiagaraUIRenderer,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANiagaraUIActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "NiagaraUIActor.h" },
		{ "ModuleRelativePath", "Public/NiagaraUIActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ANiagaraUIActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANiagaraUIActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ANiagaraUIActor_Statics::ClassParams = {
		&ANiagaraUIActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ANiagaraUIActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ANiagaraUIActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ANiagaraUIActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ANiagaraUIActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ANiagaraUIActor, 761980852);
	template<> NIAGARAUIRENDERER_API UClass* StaticClass<ANiagaraUIActor>()
	{
		return ANiagaraUIActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ANiagaraUIActor(Z_Construct_UClass_ANiagaraUIActor, &ANiagaraUIActor::StaticClass, TEXT("/Script/NiagaraUIRenderer"), TEXT("ANiagaraUIActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ANiagaraUIActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
