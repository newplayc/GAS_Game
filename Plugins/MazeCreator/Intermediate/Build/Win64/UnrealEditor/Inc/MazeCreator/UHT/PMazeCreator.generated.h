// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PMazeCreator.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MAZECREATOR_PMazeCreator_generated_h
#error "PMazeCreator.generated.h already included, missing '#pragma once' in PMazeCreator.h"
#endif
#define MAZECREATOR_PMazeCreator_generated_h

#define FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execChangeMesh);


#define FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMazeCreator(); \
	friend struct Z_Construct_UClass_AMazeCreator_Statics; \
public: \
	DECLARE_CLASS(AMazeCreator, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MazeCreator"), NO_API) \
	DECLARE_SERIALIZER(AMazeCreator)


#define FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AMazeCreator(AMazeCreator&&); \
	AMazeCreator(const AMazeCreator&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMazeCreator); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMazeCreator); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMazeCreator) \
	NO_API virtual ~AMazeCreator();


#define FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_18_PROLOG
#define FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_21_INCLASS_NO_PURE_DECLS \
	FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MAZECREATOR_API UClass* StaticClass<class AMazeCreator>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Unreal_Project_GAS_Game_Plugins_MazeCreator_Source_MazeCreator_Public_PMazeCreator_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
