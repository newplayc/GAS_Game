// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraPlayerController.h"
#include <EnhancedInputComponent.h>

#include "EnhancedInputSubsystems.h"
#include "AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Components/SplineComponent.h"
#include "EnemyInterface.h"

#include <AuraEnhancedInputComponent.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <NavigationSystem.h>



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

	//UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputPlayerSubsystem>(GetLocalPlay());
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

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CheckUnderCursor();
	AutoRun();
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D V2D = InputActionValue.Get<FVector2D>();

	show = V2D.Y;
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

	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
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
	
	bTargeting = HeightActor ? true : false;
	bAutoRunning = false;
	if (!FAuraGameplayTags::Get().Input_LMB.MatchesTagExact(ActionTag)||bTargeting || bShift)
	{
		if (GetGAS())
		{
			GetGAS()->PressFunction(ActionTag);
		}
	}


}

void AAuraPlayerController::ReleaseFunction(FGameplayTag ActionTag)
{

	if (GetGAS()){
		GetGAS()->ReleaseFunction(ActionTag);
	}

	if (!bTargeting && !bShift)
	{
		if (FollowTime <= ShortPressThreshold)
		{

			if (APawn* ConPawn = GetPawn())
			{
				UNavigationPath* Path = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), ConPawn->GetActorLocation(), CachedDestination);
				Spline->ClearSplinePoints();
				if (!Path || Path->PathPoints.Num() <= 0)
				{
					//UE_LOG(LOG_TEMP,Warning, TEXT(" No Navigation Volume"));
					return;
				}
				for (FVector& Point : Path->PathPoints)
				{
					Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World);
				}

				CachedDestination = Path->PathPoints[Path->PathPoints.Num() - 1];
			}
			bAutoRunning = true;

		}
	}
	
	FollowTime = 0.f;
	bTargeting = false;
}

void AAuraPlayerController::HeldFunction(FGameplayTag ActionTag)
{
	if (!FAuraGameplayTags::Get().Input_LMB.MatchesTagExact(ActionTag) || bTargeting||bShift)
	{
		if (GetGAS())
		{
			GetGAS()->HeldFunction(ActionTag);
		}
		return;
	}
	else 
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		if (HitResult.bBlockingHit)
		{
			CachedDestination = HitResult.Location;
		}
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
