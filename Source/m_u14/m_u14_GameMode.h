// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "m_u14_GameMode.generated.h"


UCLASS()
class M_U14_API Am_u14_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
     Am_u14_GameMode();
     virtual void BeginPlay() override ;
     virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override ;

     APlayerController* pc = nullptr ;
     AHUD* hud = nullptr ;


     void on_hudButtonPressed (uint8 type) ;

	
};
