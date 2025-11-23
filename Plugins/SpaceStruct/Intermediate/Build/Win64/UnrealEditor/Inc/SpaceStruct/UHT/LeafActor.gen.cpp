// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SpaceStruct/Public/LeafActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLeafActor() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UMaterial_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
SPACESTRUCT_API UClass* Z_Construct_UClass_ALeafActor();
SPACESTRUCT_API UClass* Z_Construct_UClass_ALeafActor_NoRegister();
UPackage* Z_Construct_UPackage__Script_SpaceStruct();
// End Cross Module References

// Begin Class ALeafActor
void ALeafActor::StaticRegisterNativesALeafActor()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALeafActor);
UClass* Z_Construct_UClass_ALeafActor_NoRegister()
{
	return ALeafActor::StaticClass();
}
struct Z_Construct_UClass_ALeafActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "LeafActor.h" },
		{ "ModuleRelativePath", "Public/LeafActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshComponent_MetaData[] = {
		{ "Category", "LeafActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/LeafActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveMat_MetaData[] = {
		{ "Category", "LeafActor" },
		{ "ModuleRelativePath", "Public/LeafActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMat_MetaData[] = {
		{ "Category", "LeafActor" },
		{ "ModuleRelativePath", "Public/LeafActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MeshComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActiveMat;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMat;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALeafActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALeafActor_Statics::NewProp_MeshComponent = { "MeshComponent", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALeafActor, MeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshComponent_MetaData), NewProp_MeshComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALeafActor_Statics::NewProp_ActiveMat = { "ActiveMat", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALeafActor, ActiveMat), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveMat_MetaData), NewProp_ActiveMat_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ALeafActor_Statics::NewProp_DefaultMat = { "DefaultMat", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ALeafActor, DefaultMat), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMat_MetaData), NewProp_DefaultMat_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ALeafActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALeafActor_Statics::NewProp_MeshComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALeafActor_Statics::NewProp_ActiveMat,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ALeafActor_Statics::NewProp_DefaultMat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALeafActor_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ALeafActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_SpaceStruct,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALeafActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALeafActor_Statics::ClassParams = {
	&ALeafActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ALeafActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ALeafActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALeafActor_Statics::Class_MetaDataParams), Z_Construct_UClass_ALeafActor_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ALeafActor()
{
	if (!Z_Registration_Info_UClass_ALeafActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALeafActor.OuterSingleton, Z_Construct_UClass_ALeafActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALeafActor.OuterSingleton;
}
template<> SPACESTRUCT_API UClass* StaticClass<ALeafActor>()
{
	return ALeafActor::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ALeafActor);
ALeafActor::~ALeafActor() {}
// End Class ALeafActor

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_SpaceStruct_Source_SpaceStruct_Public_LeafActor_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALeafActor, ALeafActor::StaticClass, TEXT("ALeafActor"), &Z_Registration_Info_UClass_ALeafActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALeafActor), 4216537383U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_SpaceStruct_Source_SpaceStruct_Public_LeafActor_h_1890767798(TEXT("/Script/SpaceStruct"),
	Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_SpaceStruct_Source_SpaceStruct_Public_LeafActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_SpaceStruct_Source_SpaceStruct_Public_LeafActor_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
