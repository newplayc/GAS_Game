// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AuraCharacter.h"


#include "AuraGameInstance.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "PlayerState/AuraPlayerState.h"
#include "PlayerController/AuraPlayerController.h"
#include "GAS/AuraAttributeSet.h"
#include "HUD/AuraHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Save/SlotSaveGame.h"


AAuraCharacter::AAuraCharacter()
{
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.0, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagara");
	LevelUpNiagaraComponent->bAutoActivate = false;
	LevelUpNiagaraComponent->SetupAttachment(RootComponent);
	LevelUpAudioComponent = CreateDefaultSubobject<UAudioComponent>("LevelUpAudioCom");
	LevelUpAudioComponent->bAutoActivate = false;
	LevelUpAudioComponent->SetupAttachment(RootComponent);
	CriticalComponent = CreateDefaultSubobject<UBuffHaloComponent>("CriticalComponent");
	CriticalComponent->SetupAttachment(RootComponent);
	HealthComponent = CreateDefaultSubobject<UBuffHaloComponent>("HealthCom");
	HealthComponent->SetupAttachment(RootComponent);
	ManaComponent = CreateDefaultSubobject<UBuffHaloComponent>("ManaCom");
	ManaComponent->SetupAttachment(RootComponent);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
}



UAbilitySystemComponent* AAuraCharacter::GetAbilitySystemComponent() const
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	if (!PS)return nullptr;
	return PS->GetAbilitySystemComponent();
}


void AAuraCharacter::OnStunTagChanged(const FGameplayTag StunTag, int32 count)
{
	Super::OnStunTagChanged(StunTag, count);
	
	bool bStun = count > 0;
	FGameplayTag AbiltyBlockTag = FAuraGameplayTags::Get().Ability_Block;
	
	if (bStun){
		AbilityComponent->AddLooseGameplayTag(AbiltyBlockTag);
	}
	else{
		AbilityComponent->RemoveLooseGameplayTag(AbiltyBlockTag);
	}
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	
	
	Super::PossessedBy(NewController);
	
	IniAbilityInfo();
	GiveStartAbilities();
	GetPlayerState<AAuraPlayerState>()->InitXpAndLevel();
	// 从存档初始化
	if(HasAuthority())
	{
		InitAuraFromSlot();
	}
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	IniAbilityInfo();
}


int32 AAuraCharacter::GetPlayerLevel_Implementation()
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		return Ps->GetPlayerLevel();
	}
	return 0;
}

void AAuraCharacter::SetLevel_Implementation(int InLevel)
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->SetLevel(InLevel);
	}
}

void AAuraCharacter::SetExp_Implementation(float InExp)
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->SetExp(InExp);
	}
}

void AAuraCharacter::AddExp_Implementation(float InExp)
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->AddExp(InExp);
	}
}

void AAuraCharacter::AddLevel_Implementation(int InLevel)
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->AddLevel(InLevel);
	}
}

void AAuraCharacter::SetSpellPoints_Implementation(int32 InPoints)
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->SetSpellPoints(InPoints);
	}
}

void AAuraCharacter::SetTalentPoints_Implementation(int32 InPoints)
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->SetTalentPoints(InPoints);
	}
}

int32 AAuraCharacter::GetExp_Implementation()
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		return Ps->GetExp();
	}
	return 0;
}

int32 AAuraCharacter::GetSpellPoints_Implementation()
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		return Ps->GetSpellPoints();
	}

	return 0;
}

int32 AAuraCharacter::GetTalentPoints_Implementation()
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		return Ps->GetTalentPoints();
	}
	return 0;
}

void AAuraCharacter::AddSpellPoints_Implementation(int32 InPoints)
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->AddSpellPoints(InPoints);
	}
}

void AAuraCharacter::AddTalentPoints_Implementation(int32 InPoints)
{
	if (AAuraPlayerState* Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->AddTalentPoints(InPoints);
	}
}

USkeletalMeshComponent* AAuraCharacter::GetWeaponMesh_Implementation()
{
	return Weapon;
}

void AAuraCharacter::SavePlayState_Implementation(const FName& PlayerStartTag)
{
	//TODO: 根据Instance的 Index 等 保存 (已完成检查点)
	if (AAuraGameModeBase* Gm = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		if (UAuraGameInstance* Gi = Cast<UAuraGameInstance>(Gm->GetGameInstance()))
		{
			if (USlotSaveGame* SlotSaveGame = Gm->LoadSlot(Gi->SlotName, Gi->SlotIndex))
			{
				// 检查点保存
				SlotSaveGame->PlayerStartTagName = PlayerStartTag;
				// 技能保存
				if(AbilityComponent)
				{
					TArray<FAbilitySave> Saves = AbilityComponent->GetAbilitySaves();
					SlotSaveGame->AbiltiySaves = Saves;
				}
				// 属性保存
				if(AAuraPlayerState * Ps = Cast<AAuraPlayerState>(GetPlayerState()))
				{
					FAttributeSave AttributeSave;
					AttributeSave.Experience = GetExp_Implementation();
					AttributeSave.SpellPoints = GetSpellPoints_Implementation();
					AttributeSave.TalentPoints= GetTalentPoints_Implementation();
					SlotSaveGame->Level = GetPlayerLevel_Implementation();
					SlotSaveGame->AttributeSave = AttributeSave;
				}
				
				// 主属性
				SlotSaveGame->PrimaryAttriuteSave.Strength = UAuraAttributeSet::GetStrengthAttribute().GetNumericValue(GetAttributeSet());
				SlotSaveGame->PrimaryAttriuteSave.Vigor = UAuraAttributeSet::GetVigorAttribute().GetNumericValue(GetAttributeSet());
				SlotSaveGame->PrimaryAttriuteSave.Intelligence = UAuraAttributeSet::GetIntelligenceAttribute().GetNumericValue(GetAttributeSet());
				SlotSaveGame->PrimaryAttriuteSave.Resilience = UAuraAttributeSet::GetResilienceAttribute().GetNumericValue(GetAttributeSet());
				Gm->SaveGame(SlotSaveGame, Gi->SlotName, Gi->SlotIndex);
				
			}
		}
	}
}

void AAuraCharacter::ShowMagicCircle_Implementation(UMaterialInterface* MaterialInterface)
{
	AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(GetController());
	PlayerController->ShowDecal(MaterialInterface);
}

void AAuraCharacter::HidenMagicCircle_Implementation()
{
	AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(GetController());
	PlayerController->HidenDecal();
}


void AAuraCharacter::OnRep_Stun() const
{
	FGameplayTag AbiltyBlockTag = FAuraGameplayTags::Get().Ability_Block;
	if (IsStun)
	{
		AbilityComponent->AddLooseGameplayTag(AbiltyBlockTag);
	}
	else
	{
		AbilityComponent->RemoveLooseGameplayTag(AbiltyBlockTag);
	}
}

void AAuraCharacter::AddPointsAfterInitAttribute(UObject* Source)
{
	AbilityComponent->ApplyEffectToInit(InitalSecondaryEffect, GetPlayerLevel_Implementation(), Source);
	AbilityComponent->ApplyEffectToInit(InitalVitalEffect, GetPlayerLevel_Implementation(), Source);
}

void AAuraCharacter::Level_up_Implementation()
{
	PlayLevelEffect();
	AddPointsAfterInitAttribute(this);
}


void AAuraCharacter::PlayLevelEffect_Implementation()
{
	LevelUpNiagaraComponent->Activate(true);

	LevelUpAudioComponent->Activate(true);
}


// 初始化GAS(GAS保存在PlayState)
void AAuraCharacter::IniAbilityInfo()
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	if (!PS)return;
	UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	check(ASC);
	AbilityComponent = ASC;
	// 初始化ASC
	ASC->InitAbilityActorInfo(PS, this);
	// 广播GAS
	OnAbilitySystemComponent.Broadcast();
	// 注册标签添加回调
	ASC->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Debuff_ElectricShock).AddUObject(
		this, &AAuraCharacter::OnStunTagChanged);

	//  初始化 AS
	UAuraAttributeSet* AS = PS->GetAttributeSet();
	AttributeSet = AS;
	// 初始化 HUD
	if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(GetController())){
		if (AAuraHUD* AHUD = Cast<AAuraHUD>(PlayerController->GetHUD())){
			AHUD->IniOverlayWidget(PS, PlayerController, ASC, AS);
		}
	}	
	// 初始化角色默认属性
	InitAttribute(this);
}

void AAuraCharacter::InitAuraFromSlot()
{
	
	if(AAuraGameModeBase  * Gm = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		if(UAuraGameInstance * Gi = Cast<UAuraGameInstance>(GetGameInstance()))
		{
			if(USlotSaveGame * SaveGame = Gm->LoadSlot(Gi->SlotName , Gi->SlotIndex))
			{
		
				// 初始化相关属性
				SetLevel_Implementation(SaveGame->Level);
				SetExp_Implementation(SaveGame->AttributeSave.Experience);
				SetSpellPoints_Implementation(SaveGame->AttributeSave.SpellPoints);
				SetTalentPoints_Implementation(SaveGame->AttributeSave.TalentPoints);

				// 初始化技能
				AbilityComponent->AddAbilityFromSlot(SaveGame->AbiltiySaves);
				
				//: 做主属性初始化
				float Strength = SaveGame->PrimaryAttriuteSave.Strength;
				float Vigor = SaveGame->PrimaryAttriuteSave.Vigor;
				float Intelligence = SaveGame->PrimaryAttriuteSave.Intelligence;
				float Resilience = SaveGame->PrimaryAttriuteSave.Resilience;
				AbilityComponent->ApplyEffectToInitWithSetByCaller(InitPrimaryAttributeFromSlot , GetPlayerLevel_Implementation() , this , Strength ,Vigor , Intelligence , Resilience);
				// 初始化其他属性
				SecondaryAndVital(this);

				
				Gm->LoadMapActors(GetWorld() , Gi->SlotName , Gi->SlotIndex);
			}
		}
	}
}


void AAuraCharacter::GiveStartAbilities()
{
	UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(AbilityComponent);
	
	// 添加基本能力
	ASC->GiveBaseAbilitiesArray(BaseAbilitys);
}
