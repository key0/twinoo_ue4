// Fill out your copyright notice in the Description page of Project Settings.

#include "m_u14.h"
#include "CH_Walker.h"
//#include "CH_Walker_AI.h"

ACH_Walker::ACH_Walker() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    auto comp0= CreateDefaultSubobject<USkeletalMeshComponent>("SK_Walker0") ;
    if ( comp0 != nullptr ) {

        auto SkeletalMesh= ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT( "/Game/myMan/Character/Mesh/SK_Walker.SK_Walker"));
        if ( SkeletalMesh.Succeeded() )
        //comp0-> SetStaticMesh ( StaticMesh.Object );
        comp0 ->SetSkeletalMesh( SkeletalMesh.Object );
    }


}

void ACH_Walker::BeginPlay() {

	Super::BeginPlay();

//_____________Set Skeletal Mesh
    //SkeletalMesh'/Game/SK_SkelCube.SK_SkelCube'
//    auto sk_mesh = LoadObject<USkeletalMesh>( this, ue4Path_sk_walker ) ;//TEXT("/Game/SK_Cube.SK_Cube") ) ;
//    if ( sk_mesh )
//         GetMesh() ->SetSkeletalMesh( sk_mesh );
//    else UE_LOG(LogTemp, Warning, TEXT("===no sk_mesh!!"));



    navSys = GetWorld() ->GetNavigationSystem();
    aiControl = Cast<AAIController>(GetController());

    if( aiControl != nullptr ) {

        FTimerHandle    timerID;
        GetWorld()->GetTimerManager().SetTimer( timerID
                                               ,this
                                               ,&ACH_Walker::randWalk
                                               ,2.0         //repeat rate sec
                                               ,true );

    }


//auto num = this ->GetComponents().Array().Num();
//UE_LOG(LogTemp, Warning, TEXT("=== num of components : %d"),num);

	
}

void ACH_Walker::randWalk() {

    if (nullptr == navSys    ) return ;
    if (nullptr == aiControl ) return ;

    FNavLocation randLocation;
    navSys ->GetRandomPointInNavigableRadius( GetActorLocation()
                                             ,500.0f
                                             ,randLocation );

    aiControl ->MoveToLocation( randLocation,0 );

}

void ACH_Walker::EndPlay(const EEndPlayReason::Type EEndPlayReason) {

    Super::EndPlay(EEndPlayReason);
    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

}

void ACH_Walker::Tick( float DeltaTime ) {

	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACH_Walker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

