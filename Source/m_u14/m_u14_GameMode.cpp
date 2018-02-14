// Fill out your copyright notice in the Description page of Project Settings.

#include "m_u14.h"
#include "m_u14_GameMode.h"
#include "m_u14_Hud.h"
#include "Algebra.h"
#include "Geometer.h"



Am_u14_GameMode::Am_u14_GameMode() {

    UE_LOG(LogTemp,Warning,TEXT("===Am_u14_GameMode::CTOR") ) ;

    //GameSessionClass = NULL;
    //GameStateClass = NULL;
    //DefaultPawnClass = NULL;
    HUDClass = Am_u14_Hud::StaticClass() ;
    //PlayerControllerClass = APlayerController::StaticClass();
   //PlayerStateClass = NULL;// CRASH ??

}

void Am_u14_GameMode::BeginPlay() {

    Super::BeginPlay();
    UE_LOG(LogTemp,Warning,TEXT("===Am_u14_GameMode::BeginPlay") ) ;

    pc = UGameplayStatics::GetPlayerController( GetWorld(), 0 ) ;
    //check(pc);

    if ( nullptr == pc ) return ;

    pc ->SetIgnoreMoveInput(  true  ) ;
    pc ->SetIgnoreLookInput(  true  ) ;
    pc ->bShowMouseCursor   = true ;
    pc ->bEnableClickEvents = true ;
    pc ->bEnableTouchEvents = true ;
    pc ->CurrentMouseCursor = EMouseCursor::Crosshairs ;



    hud = pc ->GetHUD() ;
    auto myHud = Cast< Am_u14_Hud >( hud ) ;
    if ( myHud != nullptr )
         myHud ->on_buttonPress.BindUObject( this, &Am_u14_GameMode::on_hudButtonPressed ) ;

    GWorld ->SpawnActor<AAlgebra> ( FVector(690.0 , -510.0 , 500.0 ) , FRotator::ZeroRotator ) ;
    GWorld ->SpawnActor<AGeometer>( FVector(690.0 ,  200.0 , 500.0 ) , FRotator::ZeroRotator ) ;

}

void Am_u14_GameMode::on_hudButtonPressed ( uint8 type ) {

    UE_LOG(LogTemp,Warning,TEXT("=== Am_u14_GameMode::on_hudButtonPressed!! type = %d ") , type ) ;
    if ( nullptr == pc ) return ;

    if ( type == Am_u14_Hud::startButton ) {

        pc ->SetPause( false ) ;
        return ;
    }

    if ( type == Am_u14_Hud::stopButton ) {

        pc ->SetPause( true ) ;
        return;
    }
}



void Am_u14_GameMode::EndPlay( const EEndPlayReason::Type EEndPlayReason ) {



//    TArray<AActor*> allStaticMeshActors;
//    UGameplayStatics::GetAllActorsOfClass( GetWorld()
//                                          ,AStaticMeshActor::StaticClass()
//                                          ,allStaticMeshActors );

    Super::EndPlay( EEndPlayReason );
}
