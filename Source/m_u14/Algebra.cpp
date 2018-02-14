
#include "m_u14.h"
#include "Algebra.h"


AAlgebra::AAlgebra() {

    PrimaryActorTick.bCanEverTick = false;

    auto rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootAlgebra"));
    RootComponent = rootComp;

    FString ue4Path;
    for (auto it = 0; it < digits_count ; it ++ ) {

        ue4Path = "/Game/myAlgebraGame/" + digitToString( it ) + "." + digitToString( it );//StaticMesh'/Game/dig1_.dig1_'
        ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh(*ue4Path);
        if ( Mesh.Succeeded() )
            digitMesh[ it ] = Mesh.Get() ;
    }

    for( auto it = 0; it < algebra_comps ; it ++ )
    if ( ( meshComp[ it ] = CreateDefaultSubobject<UStaticMeshComponent>(numberToName( it ))) !=nullptr ) {

           meshComp[ it ] ->SetupAttachment( rootComp );
           location[ it ] = FVector( 0.0f  , + 100 *(it%3) , - 100 *(it/3) ) ;
           meshComp[ it ] ->SetRelativeLocation( location[ it ] );
    }

//____ sound then true clicked
    auto SoundCue = ConstructorHelpers::FObjectFinder<USoundCue>( TEXT("/Game/S_16FX.S_16FX") ) ;
    if ( SoundCue.Succeeded() )
         sound_16FX = SoundCue.Object ;

}

void AAlgebra::BeginPlay() {

    UE_LOG(LogTemp, Warning, TEXT( "=== Algebra::BeginPlay") ) ;
	Super::BeginPlay();

    for (auto it : meshComp)
              it ->OnClicked.AddDynamic( this, &AAlgebra::on_CompClicked );

    auto
    actorLocation = GetActorLocation();
    actorLocation.Y += 100.f ;
    actorLocation.Z -= 200.f ;

    gameTimer = GWorld ->SpawnActor<ASubGameTimer>( actorLocation , FRotator::ZeroRotator ) ;

    raund();// first algebra game
}

void AAlgebra::raund() {

    isNewRaund = true ;

    //============== SET RANDOM DIGIT argument ONE ===================
    auto r1 = FMath::RandHelper( digits_count - 1 );
    meshComp [ arg1 ] ->SetStaticMesh( digitMesh[ r1 ] );
    meshComp [ oper ] ->SetStaticMesh( digitMesh[ operAdd ] );
    //============== SET RANDOM DIGIT argument TWO ===================
    auto r2 = FMath::RandHelper( digits_count - 1 );
    meshComp [ arg2 ] ->SetStaticMesh( digitMesh[ r2 ] );

    //============ SET TRUE ANSWER TO res1
    meshComp [ res1 ] ->SetStaticMesh( digitMesh[ (r1 + r2) % ( digits_count-1 ) ] );

    //============ SET ANOTHER (FALSE?) 2 ANSWER
    r1 = FMath::RandHelper( digits_count - 1 );
    meshComp [ res2 ] ->SetStaticMesh( digitMesh[ r1 ] );

    //=========== CONTINUE ...
    r2 = FMath::RandHelper( digits_count - 1 );
    meshComp [ res3 ] ->SetStaticMesh( digitMesh[ r2 ] );

    // RANDOM LOCATION RES 1 2 3 TO HIDDEN ANSWER ( res1 ) and SHOW RANDOM FIRST
    auto r = FMath::RandHelper(3);
    meshComp [ res1 ] ->SetRelativeLocation( location[ res1 + (r + 0) % 3 ] );
    meshComp [ res2 ] ->SetRelativeLocation( location[ res1 + (r + 1) % 3 ] );
    meshComp [ res3 ] ->SetRelativeLocation( location[ res1 + (r + 2) % 3 ] );

    if ( timerID.IsValid() )
         GWorld ->GetTimerManager().ClearTimer( timerID );

    GWorld ->GetTimerManager().SetTimer( timerID
                                        ,this
                                        ,&AAlgebra::raundUpdate
                                        ,timerRate  //repeat rate sec
                                        ,true  );  // to repeat

}

void AAlgebra::raundUpdate() {

    static bool isStartAnimation = true       ;
                isStartAnimation = isNewRaund ;

    if ( isStartAnimation ) { //  need play startanimation at new raund

        static float pos = 0         ;
                     pos+= pos/7 + 1 ;

        if ( pos <= 100) {

            pos > 90 ? pos = 100 : pos ;
            //UE_LOG(LogTemp, Warning, TEXT( "=== pos =%f") , pos ) ;

            meshComp [ arg1 ] ->SetRelativeLocation( location[ arg1 ] + FVector (0, pos - 100 ,0 ) );
            meshComp [ arg2 ] ->SetRelativeLocation( location[ arg2 ] + FVector (0, 100 - pos ,0 ) );
            meshComp [ oper ] ->SetRelativeLocation( location[ oper ] + FVector (0, 0 ,100 - pos ) );


        } else {

            isNewRaund = false ;
            pos = 0 ;

        }

    }

// static float dPos  =0 ;//, pos2  =0 , pos3  =0 ;
//                 dPos < 3.141592f ? dPos += 0.1f : dPos -=3.141592f ;//, pos2 +=4 , pos3 +=1 ;

//    meshComp [ res1 ] ->SetRelativeLocation( res1Location + FVector( 0 ,5* FMath::Cos(  1*dPos ) , 0  ) );
//    meshComp [ res2 ] ->SetRelativeLocation( res2Location + FVector( 0 ,5* FMath::Cos(  2*dPos ) , 0  ) );
//    meshComp [ res3 ] ->SetRelativeLocation( res3Location + FVector( 0 ,5* FMath::Sin(  3*dPos ) , 0  ) );

// meshComp [ res1 ] ->SetRelativeRotation( FRotator( FMath::Sin(rot1) ,FMath::Cos(rot2) , 0  ) );
// meshComp [ res2 ] ->SetRelativeRotation( FRotator( rot2 ,rot1 , 0    ) );
// meshComp [ res3 ] ->SetRelativeRotation( FRotator( rot1 ,rot2 , rot3 ) );

//    else gameOver();
}

//void AAlgebra::gameOver(){

//GetWorld()->GetTimerManager().ClearTimer(timerID);

////UGameplayStatics::PlaySoundAtLocation(this, soundBoom, GetActorLocation());
////UGameplayStatics::PlaySound2D(this,soundBoom);

//EndPlay( EEndPlayReason::Quit );
//}

void AAlgebra::on_CompClicked( UPrimitiveComponent* ClickedComp, FKey ButtonClicked ) {

    if( ClickedComp ->GetName().Equals("res1") ) {

        if ( gameTimer != nullptr )
             gameTimer ->isNewRaund = true ;
        if ( sound_16FX!= nullptr )
             UGameplayStatics::PlaySoundAtLocation( this, sound_16FX, GetActorLocation() ) ;

        isNewRaund = true ;// start new algebra game raund
        raund();

    } else UE_LOG(LogTemp, Warning, TEXT("=== FALSE ANSWER ") );
}

void AAlgebra::EndPlay( const EEndPlayReason::Type EEndPlayReason ) {

    GWorld ->GetTimerManager().ClearAllTimersForObject( this );
	Super::EndPlay( EEndPlayReason );

    UE_LOG(LogTemp, Warning, TEXT("=== AAlgebra::EndPlay ") );

}

