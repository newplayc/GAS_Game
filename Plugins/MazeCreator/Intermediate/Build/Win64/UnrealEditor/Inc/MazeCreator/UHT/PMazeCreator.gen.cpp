// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MazeCreator/Public/PMazeCreator.h"
#include "Runtime/Engine/Classes/Engine/TimerHandle.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePMazeCreator() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTimerHandle();
MAZECREATOR_API UClass* Z_Construct_UClass_AMazeCreator();
MAZECREATOR_API UClass* Z_Construct_UClass_AMazeCreator_NoRegister();
UPackage* Z_Construct_UPackage__Script_MazeCreator();
// End Cross Module References

// Begin Class AMazeCreator Function ChangeMesh
struct Z_Construct_UFunction_AMazeCreator_ChangeMesh_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMazeCreator_ChangeMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMazeCreator, nullptr, "ChangeMesh", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMazeCreator_ChangeMesh_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMazeCreator_ChangeMesh_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMazeCreator_ChangeMesh()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMazeCreator_ChangeMesh_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMazeCreator::execChangeMesh)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ChangeMesh();
	P_NATIVE_END;
}
// End Class AMazeCreator Function ChangeMesh

// Begin Class AMazeCreator
void AMazeCreator::StaticRegisterNativesAMazeCreator()
{
	UClass* Class = AMazeCreator::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ChangeMesh", &AMazeCreator::execChangeMesh },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMazeCreator);
UClass* Z_Construct_UClass_AMazeCreator_NoRegister()
{
	return AMazeCreator::StaticClass();
}
struct Z_Construct_UClass_AMazeCreator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "PMazeCreator.h" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultRoot_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnStaticMeshes_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlockMesh_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlaneMesh_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshWidth_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_playRate_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_creationMode_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "0 \xe4\xbd\xbf\xe7\x94\xa8""dfs\xe7\x94\x9f\xe6\x88\x90 \xe6\x8b\xa5\xe6\x9c\x89 \xe6\x98\x8e\xe6\x98\xbe\xe7\x9a\x84\xe4\xb8\xbb\xe8\xb7\xaf, 1  \xe6\x8b\xa5\xe6\x9c\x89\xe6\x9b\xb4\xe5\xa4\x9a\xe7\x9a\x84\xe5\x88\x86\xe5\xb2\x94\xe8\xb7\xaf , 2 \xe6\x8b\xa5\xe6\x9c\x89 \xe6\x96\xb9\xe5\x9d\x97\xe5\xbd\xa2 \xe7\x9a\x84 \xe6\xb4\xbb\xe5\x8a\xa8\xe5\x8c\xba\xe5\x9f\x9f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimerHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomNum_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "ClampMax", "1.000000" },
		{ "ClampMin", "0.000000" },
		{ "EditCondition", "creationMode == 2" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomSize_MetaData[] = {
		{ "Category", "MazeCreator" },
		{ "ClampMax", "1.000000" },
		{ "ClampMin", "0.000000" },
		{ "EditCondition", "creationMode == 2" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/PMazeCreator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultRoot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnStaticMeshes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SpawnStaticMeshes;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BlockMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlaneMesh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeshWidth;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Width;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Height;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_playRate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_creationMode;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TimerHandle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RoomNum;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RoomSize;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMazeCreator_ChangeMesh, "ChangeMesh" }, // 560901492
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMazeCreator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_DefaultRoot = { "DefaultRoot", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, DefaultRoot), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultRoot_MetaData), NewProp_DefaultRoot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_SpawnStaticMeshes_Inner = { "SpawnStaticMeshes", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_SpawnStaticMeshes = { "SpawnStaticMeshes", nullptr, (EPropertyFlags)0x0020088000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, SpawnStaticMeshes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnStaticMeshes_MetaData), NewProp_SpawnStaticMeshes_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_BlockMesh = { "BlockMesh", nullptr, (EPropertyFlags)0x0124080000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, BlockMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlockMesh_MetaData), NewProp_BlockMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_PlaneMesh = { "PlaneMesh", nullptr, (EPropertyFlags)0x0124080000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, PlaneMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlaneMesh_MetaData), NewProp_PlaneMesh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_MeshWidth = { "MeshWidth", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, MeshWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshWidth_MetaData), NewProp_MeshWidth_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, Width), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Width_MetaData), NewProp_Width_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, Height), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Height_MetaData), NewProp_Height_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_playRate = { "playRate", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, playRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_playRate_MetaData), NewProp_playRate_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_creationMode = { "creationMode", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, creationMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_creationMode_MetaData), NewProp_creationMode_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_TimerHandle = { "TimerHandle", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, TimerHandle), Z_Construct_UScriptStruct_FTimerHandle, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimerHandle_MetaData), NewProp_TimerHandle_MetaData) }; // 756291145
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_RoomNum = { "RoomNum", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, RoomNum), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomNum_MetaData), NewProp_RoomNum_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMazeCreator_Statics::NewProp_RoomSize = { "RoomSize", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMazeCreator, RoomSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomSize_MetaData), NewProp_RoomSize_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMazeCreator_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_DefaultRoot,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_SpawnStaticMeshes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_SpawnStaticMeshes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_BlockMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_PlaneMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_MeshWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_Width,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_Height,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_playRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_creationMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_TimerHandle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_RoomNum,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMazeCreator_Statics::NewProp_RoomSize,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMazeCreator_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMazeCreator_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_MazeCreator,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMazeCreator_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMazeCreator_Statics::ClassParams = {
	&AMazeCreator::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMazeCreator_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMazeCreator_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMazeCreator_Statics::Class_MetaDataParams), Z_Construct_UClass_AMazeCreator_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMazeCreator()
{
	if (!Z_Registration_Info_UClass_AMazeCreator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMazeCreator.OuterSingleton, Z_Construct_UClass_AMazeCreator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMazeCreator.OuterSingleton;
}
template<> MAZECREATOR_API UClass* StaticClass<AMazeCreator>()
{
	return AMazeCreator::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMazeCreator);
AMazeCreator::~AMazeCreator() {}
// End Class AMazeCreator

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMazeCreator, AMazeCreator::StaticClass, TEXT("AMazeCreator"), &Z_Registration_Info_UClass_AMazeCreator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMazeCreator), 3191299896U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_4151195758(TEXT("/Script/MazeCreator"),
	Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
