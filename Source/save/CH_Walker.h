// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "CH_Walker.generated.h"

UCLASS()
class M_U14_API ACH_Walker : public ACharacter {

	GENERATED_BODY()

    #define ue4Path_sk_walker TEXT("SkeletalMesh'/Game/myMan/Character/Mesh/SK_Walker.SK_Walker'")

    ACH_Walker();
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    AAIController* aiControl  ;
    UNavigationSystem* navSys ;

    UFUNCTION()
    void randWalk();
	
};
