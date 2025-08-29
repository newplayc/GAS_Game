// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherActor/AuraDecalActor.h"
#include "Components/DecalComponent.h"


AAuraDecalActor::AAuraDecalActor()
{
	PrimaryActorTick.bCanEverTick = false;
	DecalComponent = CreateDefaultSubobject<UDecalComponent>("DecalCom");
	RootComponent = DecalComponent;
	
}

