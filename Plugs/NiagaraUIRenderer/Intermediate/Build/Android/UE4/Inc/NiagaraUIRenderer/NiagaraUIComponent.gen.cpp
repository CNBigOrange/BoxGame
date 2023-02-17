// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NiagaraUIRenderer/Public/NiagaraUIComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNiagaraUIComponent() {}
// Cross Module References
	NIAGARAUIRENDERER_API UClass* Z_Construct_UClass_UNiagaraUIComponent_NoRegister();
	NIAGARAUIRENDERER_API UClass* Z_Construct_UClass_UNiagaraUIComponent();
	NIAGARA_API UClass* Z_Construct_UClass_UNiagaraComponent();
	UPackage* Z_Construct_UPackage__Script_NiagaraUIRenderer();
// End Cross Module References
	void UNiagaraUIComponent::StaticRegisterNativesUNiagaraUIComponent()
	{
	}
	UClass* Z_Construct_UClass_UNiagaraUIComponent_NoRegister()
	{
		return UNiagaraUIComponent::StaticClass();
	}
	struct Z_Construct_UClass_UNiagaraUIComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNiagaraUIComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UNiagaraComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_NiagaraUIRenderer,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNiagaraUIComponent_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Object Physics Collision Mobility VirtualTexture" },
		{ "IncludePath", "NiagaraUIComponent.h" },
		{ "ModuleRelativePath", "Public/NiagaraUIComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNiagaraUIComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNiagaraUIComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UNiagaraUIComponent_Statics::ClassParams = {
		&UNiagaraUIComponent::StaticClass,
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
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UNiagaraUIComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraUIComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UNiagaraUIComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UNiagaraUIComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UNiagaraUIComponent, 3881658287);
	template<> NIAGARAUIRENDERER_API UClass* StaticClass<UNiagaraUIComponent>()
	{
		return UNiagaraUIComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNiagaraUIComponent(Z_Construct_UClass_UNiagaraUIComponent, &UNiagaraUIComponent::StaticClass, TEXT("/Script/NiagaraUIRenderer"), TEXT("UNiagaraUIComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNiagaraUIComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
