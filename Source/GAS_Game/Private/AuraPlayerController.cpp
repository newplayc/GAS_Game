// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraPlayerController.h"
#include <EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"
#include "EnemyInterface.h"



AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	HeightActor = nullptr;
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

	UEnhancedInputComponent* EnhancedInputCom = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputCom->BindAction(MoveAction, ETriggerEvent::Triggered,this,  &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CheckUnderCursor();
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

void AAuraPlayerController::CheckUnderCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	if (!HitResult.bBlockingHit)return;
	IEnemyInterface* HitActor = Cast<IEnemyInterface>(HitResult.GetActor());
	if (HitActor == nullptr &&HeightActor!=nullptr){
		HeightActor->UnHeightLightActor();
	}
	else if(HitActor!=nullptr){ 
		if(HeightActor != nullptr)
			HeightActor->UnHeightLightActor();

			HeightActor = HitActor;
			HeightActor->HeightLightActor();
	}
}
