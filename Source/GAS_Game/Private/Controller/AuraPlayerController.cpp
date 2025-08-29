// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "Tag/AuraGameplayTags.h"
#include "Components/SplineComponent.h"
#include "Interface/EnemyInterface.h"
#include "GameplayTagContainer.h"
#include "NavigationPath.h"
#include "Component/AuraEnhancedInputComponent.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <NavigationSystem.h>

#include "AuraBlueprintFunctionLibrary.h"
#include "InputMappingContext.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"

void AAuraPlayerController::SetLifeSiphonText_Implementation(ACharacter* ECharacter,
                                                             const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(IsValid(DamageTextWidgetClass))
	{
		UDamageTextWidgetCom * DamageWidget = NewObject<UDamageTextWidgetCom>(ECharacter , DamageTextWidgetClass);
		DamageWidget->RegisterComponent();
		DamageWidget->AttachToComponent(ECharacter->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform);
		float LifeSiphon = UAuraBlueprintFunctionLibrary::GetLifeSiphon(EffectContextHandle);
		DamageWidget->SetLifeSiphonText(LifeSiphon);
	}
}

void AAuraPlayerController::SetManaSiphonText_Implementation(ACharacter* ECharacter,
	const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(IsValid(DamageTextWidgetClass))
	{
		UDamageTextWidgetCom * DamageWidget = NewObject<UDamageTextWidgetCom>(ECharacter , DamageTextWidgetClass);
		DamageWidget->RegisterComponent();
		DamageWidget->AttachToComponent(ECharacter->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform);
		float ManaSiphon = UAuraBlueprintFunctionLibrary::GetManaSiphon(EffectContextHandle);
		DamageWidget->SetManaSiphonText(ManaSiphon);
	}
}

void AAuraPlayerController::ShowDecal(UMaterialInterface * DecalMaterial)
{
	
	if(!IsValid(DecalActorInstance) && IsLocalController())
	{
		DecalActorInstance = GetWorld()->SpawnActor<AAuraDecalActor>(DecalActorClass);
		DecalActorInstance->DecalComponent->SetMaterial(0,DecalMaterial);
	}
}

void AAuraPlayerController::HidenDecal()
{
	if(IsValid(DecalActorInstance))
	{
		DecalActorInstance->Destroy();
		DecalActorInstance = nullptr;
	}
}

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	HeightActor = nullptr;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	
	 UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	 if (!Subsystem)return;
	 Subsystem->AddMappingContext(AuraContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraEnhancedInputComponent* EnhancedInputCom = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	
	EnhancedInputCom->BindAction(MoveAction, ETriggerEvent::Triggered , this,  &AAuraPlayerController::Move);
	EnhancedInputCom->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftStart);

	EnhancedInputCom->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftEnd);

	EnhancedInputCom->BindAbilityActions(InputAction, this, &AAuraPlayerController::PressFunction, &AAuraPlayerController::ReleaseFunction, &AAuraPlayerController::HeldFunction);

}


void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning)return; 
	APawn* ControlPawn = GetPawn();
	if (!ControlPawn)return;
	const FVector SplineLocation = Spline->FindLocationClosestToWorldLocation(ControlPawn->GetActorLocation(), ESplineCoordinateSpace::World);
	const FVector SplineDirection = Spline->FindDirectionClosestToWorldLocation(ControlPawn->GetActorLocation(), ESplineCoordinateSpace::World);
	
	ControlPawn->AddMovementInput(SplineDirection);
	double Distance = (SplineLocation  - CachedDestination).Length();
	if (Distance <= ShortPressThreshold)
	{
		bAutoRunning = false;
	}
}

void AAuraPlayerController::UpdateDecal()
{
	if(IsValid(DecalActorInstance))
	{
		DecalActorInstance->SetActorLocation(HitResult.ImpactPoint);
	}
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CheckUnderCursor();
	UpdateDecal();
	AutoRun();
}

void AAuraPlayerController::SetDamageText_Implementation(float Damage, ACharacter* ECharacter,
	const FGameplayEffectContextHandle& EffectContextHandle)
{
	
	if(IsValid(DamageTextWidgetClass))
	{
		UDamageTextWidgetCom * DamageWidget = NewObject<UDamageTextWidgetCom>(ECharacter , DamageTextWidgetClass);
		DamageWidget->RegisterComponent();
		DamageWidget->AttachToComponent(ECharacter->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform);
		bool Block = UAuraBlueprintFunctionLibrary::GetGameContextBlock(EffectContextHandle);
		bool Critical = UAuraBlueprintFunctionLibrary::GetGameContextCritical(EffectContextHandle);
		
		
		FGameplayTag DamageType = UAuraBlueprintFunctionLibrary::GetDamageTypeTag(EffectContextHandle);
		DamageWidget->SetDamageText(Damage , Block ,Critical, DamageType);
	}
	
}


void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D V2D = InputActionValue.Get<FVector2D>();
	
	const FRotator YRotator(0, GetControlRotation().Yaw, 0);
	const FVector ForwardVector = FRotationMatrix(YRotator).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YRotator).GetUnitAxis(EAxis::Y);

	
	if (APawn* ControlPawn = GetPawn())
	{
		ControlPawn->AddMovementInput(ForwardVector, V2D.Y, false); 
		ControlPawn->AddMovementInput(RightVector, V2D.X, false);
	}
}

void AAuraPlayerController::ShiftStart()
{
	bShift = true;
}

void AAuraPlayerController::ShiftEnd()
{
	bShift = false;
}

void AAuraPlayerController::CheckUnderCursor()
{

	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (!HitResult.bBlockingHit)return;
	IEnemyInterface* HitActor = Cast<IEnemyInterface>(HitResult.GetActor());
	
	if (HeightActor != HitActor)
	{
		if(HeightActor) {
			HeightActor->UnHeightLightActor();
		}
		if (HitActor) {
		
			HitActor->HeightLightActor();
		}
	}
	HeightActor = HitActor;
}

void AAuraPlayerController::PressFunction(FGameplayTag ActionTag)
{
	// 检测 是否有  技能阻挡标签
	if(GetGAS()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Ability_Block)) return;
	bTargeting = HeightActor ? true : false;
	bAutoRunning = false;

	// 如果 目标 或者 按下Shift 释放技能。
	if (!FAuraGameplayTags::Get().Input_LMB.MatchesTagExact(ActionTag)||bTargeting || bShift)
	{
		if (GetGAS())
     	{   // 触发 GAS 按压事件
     		GetGAS()->PressFunction(ActionTag);
     	}
    }
	else
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this , ClickIcon ,HitResult.Location);
	}
}
/*
 * 如果按压时间短会触发 点击自动寻路
 */
void AAuraPlayerController::ReleaseFunction(FGameplayTag ActionTag)
{
	// 松开技能 
	if (GetGAS()){
		// 松开技能按键 通知
		GetGAS()->ReleaseFunction(ActionTag);
	}
	
	if(GetGAS()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Ability_Block)) return;
	// 是否 需要 判断行走
	if (!bTargeting && !bShift && FAuraGameplayTags::Get().Input_LMB.MatchesTagExact(ActionTag) )
	{    //   按压积累时间 小于 这个门槛 ， 判断为 一次 短点击  可以行走
		if (FollowTime <= ShortPressThreshold)
		{
			if (APawn* ConPawn = GetPawn())
			{
				UNavigationPath* Path = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), ConPawn->GetActorLocation(), CachedDestination);
				Spline->ClearSplinePoints();
				if (!Path || Path->PathPoints.Num() <= 0)
				{
					return;
				}
				for (FVector& Point : Path->PathPoints)
				{
					Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World);
				}
				// 缓存 自动寻路结尾
				CachedDestination = Path->PathPoints[Path->PathPoints.Num() - 1];
			}
			
			bAutoRunning = true;

		}
	}
	
	FollowTime = 0.f;
	bTargeting = false;
}
/*
 *计算按压时间 
 */
void AAuraPlayerController::HeldFunction(FGameplayTag ActionTag)
{
	if (!FAuraGameplayTags::Get().Input_LMB.MatchesTagExact(ActionTag) || bTargeting||bShift)
	{
		if (GetGAS())
		{
			GetGAS()->HeldFunction(ActionTag);
		}
	}
	else 
	{
		if(GetGAS()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Ability_Block)) return;
		// 积累 按压时间
		FollowTime += GetWorld()->GetDeltaSeconds();

		if (HitResult.bBlockingHit)
		{
			CachedDestination = HitResult.Location;
		}
		// 一直 按着  就一直 走
		if (APawn* ConPawn = GetPawn())
		{
			FVector Direction = (CachedDestination - ConPawn->GetActorLocation()).GetSafeNormal();
			ConPawn->AddMovementInput(Direction, 1, false);
		}
	}
	
}

 UAuraAbilitySystemComponent* AAuraPlayerController::GetGAS()
{
	if(AbilitySystemCom == nullptr)
	AbilitySystemCom =  Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	return AbilitySystemCom;
}