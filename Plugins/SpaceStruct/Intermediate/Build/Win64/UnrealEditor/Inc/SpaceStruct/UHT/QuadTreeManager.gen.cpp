// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SpaceStruct/Public/QuadTreeManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeQuadTreeManager() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
SPACESTRUCT_API UClass* Z_Construct_UClass_ALeafActor_NoRegister();
SPACESTRUCT_API UClass* Z_Construct_UClass_AQuadTreeManager();
SPACESTRUCT_API UClass* Z_Construct_UClass_AQuadTreeManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_SpaceStruct();
// End Cross Module References

// Begin Class AQuadTreeManager
void AQuadTreeManager::StaticRegisterNativesAQuadTreeManager()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AQuadTreeManager);
UClass* Z_Construct_UClass_AQuadTreeManager_NoRegister()
{
	return AQuadTreeManager::StaticClass();
}
struct Z_Construct_UClass_AQuadTreeManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe5\x9b\x9b\xe5\x8f\x89\xe6\xa0\x91\xe7\xae\xa1\xe7\x90\x86\xe5\x99\xa8 - \xe7\x94\xa8\xe4\xba\x8e\xe7\xa9\xba\xe9\x97\xb4\xe5\x88\x86\xe5\x8c\xba\xe5\x92\x8c\xe7\xa2\xb0\xe6\x92\x9e\xe6\xa3\x80\xe6\xb5\x8b\xe4\xbc\x98\xe5\x8c\x96\n */" },
#endif
		{ "IncludePath", "QuadTreeManager.h" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9b\x9b\xe5\x8f\x89\xe6\xa0\x91\xe7\xae\xa1\xe7\x90\x86\xe5\x99\xa8 - \xe7\x94\xa8\xe4\xba\x8e\xe7\xa9\xba\xe9\x97\xb4\xe5\x88\x86\xe5\x8c\xba\xe5\x92\x8c\xe7\xa2\xb0\xe6\x92\x9e\xe6\xa3\x80\xe6\xb5\x8b\xe4\xbc\x98\xe5\x8c\x96" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RootCom_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\xbb\x84\xe4\xbb\xb6\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xbb\x84\xe4\xbb\xb6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Checker_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnPoint1_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnPoint2_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnPoint3_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnPoint4_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[] = {
		{ "Category", "QuadTree" },
		{ "ClampMin", "100.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x9b\x9b\xe5\x8f\x89\xe6\xa0\x91\xe9\x85\x8d\xe7\xbd\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9b\x9b\xe5\x8f\x89\xe6\xa0\x91\xe9\x85\x8d\xe7\xbd\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[] = {
		{ "Category", "QuadTree" },
		{ "ClampMin", "100.0" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CheckRadius_MetaData[] = {
		{ "Category", "QuadTree" },
		{ "ClampMin", "1.0" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxActorCount_MetaData[] = {
		{ "Category", "Spawning" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x94\x9f\xe6\x88\x90\xe9\x85\x8d\xe7\xbd\xae\n" },
#endif
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x94\x9f\xe6\x88\x90\xe9\x85\x8d\xe7\xbd\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeafActorClass_MetaData[] = {
		{ "Category", "Spawning" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnRate_MetaData[] = {
		{ "Category", "Spawning" },
		{ "ClampMin", "0.1" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveSpeed_MetaData[] = {
		{ "Category", "Spawning" },
		{ "ClampMin", "10.0" },
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnedActors_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x94\x9f\xe6\x88\x90\xe7\x9a\x84""Actor\xe5\x88\x97\xe8\xa1\xa8\n" },
#endif
		{ "ModuleRelativePath", "Public/QuadTreeManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x94\x9f\xe6\x88\x90\xe7\x9a\x84""Actor\xe5\x88\x97\xe8\xa1\xa8" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RootCom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Checker;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnPoint1;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnPoint2;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnPoint3;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnPoint4;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_Width;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_Height;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CheckRadius;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxActorCount;
	static const UECodeGen_Private::FClassPropertyParams NewProp_LeafActorClass;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpawnRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveSpeed;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnedActors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SpawnedActors;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AQuadTreeManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_RootCom = { "RootCom", nullptr, (EPropertyFlags)0x01240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, RootCom), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RootCom_MetaData), NewProp_RootCom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_Checker = { "Checker", nullptr, (EPropertyFlags)0x01240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, Checker), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Checker_MetaData), NewProp_Checker_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnPoint1 = { "SpawnPoint1", nullptr, (EPropertyFlags)0x01240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, SpawnPoint1), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnPoint1_MetaData), NewProp_SpawnPoint1_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnPoint2 = { "SpawnPoint2", nullptr, (EPropertyFlags)0x01240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, SpawnPoint2), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnPoint2_MetaData), NewProp_SpawnPoint2_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnPoint3 = { "SpawnPoint3", nullptr, (EPropertyFlags)0x01240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, SpawnPoint3), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnPoint3_MetaData), NewProp_SpawnPoint3_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnPoint4 = { "SpawnPoint4", nullptr, (EPropertyFlags)0x01240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, SpawnPoint4), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnPoint4_MetaData), NewProp_SpawnPoint4_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, Width), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Width_MetaData), NewProp_Width_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, Height), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Height_MetaData), NewProp_Height_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_CheckRadius = { "CheckRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, CheckRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CheckRadius_MetaData), NewProp_CheckRadius_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_MaxActorCount = { "MaxActorCount", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, MaxActorCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxActorCount_MetaData), NewProp_MaxActorCount_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_LeafActorClass = { "LeafActorClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, LeafActorClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ALeafActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeafActorClass_MetaData), NewProp_LeafActorClass_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnRate = { "SpawnRate", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, SpawnRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnRate_MetaData), NewProp_SpawnRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_MoveSpeed = { "MoveSpeed", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, MoveSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveSpeed_MetaData), NewProp_MoveSpeed_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnedActors_Inner = { "SpawnedActors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_ALeafActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnedActors = { "SpawnedActors", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AQuadTreeManager, SpawnedActors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnedActors_MetaData), NewProp_SpawnedActors_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AQuadTreeManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_RootCom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_Checker,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnPoint1,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnPoint2,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnPoint3,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnPoint4,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_Width,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_Height,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_CheckRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_MaxActorCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_LeafActorClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_MoveSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnedActors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQuadTreeManager_Statics::NewProp_SpawnedActors,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AQuadTreeManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AQuadTreeManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_SpaceStruct,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AQuadTreeManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AQuadTreeManager_Statics::ClassParams = {
	&AQuadTreeManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AQuadTreeManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AQuadTreeManager_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AQuadTreeManager_Statics::Class_MetaDataParams), Z_Construct_UClass_AQuadTreeManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AQuadTreeManager()
{
	if (!Z_Registration_Info_UClass_AQuadTreeManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AQuadTreeManager.OuterSingleton, Z_Construct_UClass_AQuadTreeManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AQuadTreeManager.OuterSingleton;
}
template<> SPACESTRUCT_API UClass* StaticClass<AQuadTreeManager>()
{
	return AQuadTreeManager::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AQuadTreeManager);
AQuadTreeManager::~AQuadTreeManager() {}
// End Class AQuadTreeManager

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_SpaceStruct_Source_SpaceStruct_Public_QuadTreeManager_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AQuadTreeManager, AQuadTreeManager::StaticClass, TEXT("AQuadTreeManager"), &Z_Registration_Info_UClass_AQuadTreeManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AQuadTreeManager), 275265639U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_SpaceStruct_Source_SpaceStruct_Public_QuadTreeManager_h_3380986826(TEXT("/Script/SpaceStruct"),
	Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_SpaceStruct_Source_SpaceStruct_Public_QuadTreeManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_SpaceStruct_Source_SpaceStruct_Public_QuadTreeManager_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
