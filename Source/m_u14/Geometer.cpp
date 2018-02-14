
#include "m_u14.h"
#include "Geometer.h"
//#include "m_u14_GameMode.h"

AGeometer::AGeometer() {

    PrimaryActorTick.bCanEverTick = false ;

//_____________ LOAD Meshes for geom forms

    auto rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootGeometer"));
    RootComponent = rootComp;

    FString ue4Path;

    for (auto it = 0; it < forms_count ; it ++ ) {

        ue4Path = "/Game/myGeometryGame/" + formToString( it ) + "." + formToString( it );//StaticMesh'/Game/dig1_.dig1_'
        ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh( *ue4Path );
        if ( Mesh.Succeeded() )
             formMesh[ it ] = Mesh.Get();
    }

    for( auto it = 0; it < geometer_comps ; it ++ )
    if ( ( meshComp[ it ] = CreateDefaultSubobject<UStaticMeshComponent>( compToName( it ))) !=nullptr ) {

           meshComp[ it ] ->SetupAttachment( rootComp ); //meshComp[ it ] ->AttachTo(rootComp); // UE 410
           location[ it ] = FVector( 0.0f  , + 100 *(it%3) , - 100 *(it/3) ) ;
           meshComp[ it ] ->SetRelativeLocation( location[ it ] );

    }
//____ sound then true clicked
    auto SoundCue = ConstructorHelpers::FObjectFinder<USoundCue>( TEXT("/Game/S_14Bitz.S_14Bitz") ) ;
    if ( SoundCue.Succeeded() )
             sound_14Bitz = SoundCue.Object ;


}

void AGeometer::BeginPlay() {

    UE_LOG(LogTemp, Warning, TEXT( "=== AGeometer::BeginPlay") ) ;
    Super::BeginPlay();

    for ( auto it : meshComp )
               it ->OnClicked.AddDynamic( this, &AGeometer::on_CompClicked );
    auto
    actorLocation = GetActorLocation();
    actorLocation.Y += 100.f ;
    actorLocation.Z -= 200.f ;
    gameTimer = GWorld ->SpawnActor<ASubGameTimer>( actorLocation , FRotator::ZeroRotator ) ;

    raund();// first geometry game
}

void AGeometer::raund() {

    isNewRaund = true ;

    auto it = randAddAbleForms() ;
    auto r  = FMath::RandHelper( forms_count -1 ) ;
    auto r2 = FMath::RandHelper( forms_count -1 ) ;

//============== SET RANDOM DIGIT argument ONE ===================

    meshComp [ arg1 ] ->SetStaticMesh( formMesh[ it.A    ] );
    meshComp [ oper ] ->SetStaticMesh( formMesh[ operAdd ] );
//============== SET RANDOM DIGIT argument TWO ===================

    meshComp [ arg2 ] ->SetStaticMesh( formMesh[ it.B    ] );

//============ SET TRUE ANSWER TO res1
    meshComp [ res1 ] ->SetStaticMesh( formMesh[ it.AB   ] );

//============ SET ANOTHER (FALSE) 2 ANSWER
    while ( r == it.AB )
            r = FMath::RandHelper( forms_count -1 )    ;// -1 == -oper
    meshComp [ res2 ] ->SetStaticMesh( formMesh[ r ]  );

//=========== CONTINUE ...
    while ( r2 == r || r2 == it.AB )
            r2 = FMath::RandHelper( forms_count -1 )   ;// -1 == -oper
    meshComp [ res3 ] ->SetStaticMesh( formMesh[ r2 ] );

//RANDOM LOCATION RES 1 2 3 TO HIDDEN ANSWER ( res1 )
    r = FMath::RandHelper(3);

    meshComp [ res1 ] ->SetRelativeLocation( location[ res1 + (r + 0) % 3 ] );
    meshComp [ res2 ] ->SetRelativeLocation( location[ res1 + (r + 1) % 3 ] );
    meshComp [ res3 ] ->SetRelativeLocation( location[ res1 + (r + 2) % 3 ] );

    if ( timerID.IsValid() )
         GWorld ->GetTimerManager().ClearTimer( timerID );

    GWorld ->GetTimerManager().SetTimer( timerID
                                        ,this
                                        ,&AGeometer::raundUpdate
                                        ,timerRate  //repeat rate sec
                                        ,true  );  //is to repeat

   // UE_LOG(LogTemp, Warning, TEXT( "=== NOW isPause =%d") , isPause ) ;

}

void AGeometer::raundUpdate() {

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

    } else {

        static float rot1  =0 , rot2  =0 , rot3  =0 ;
                     rot1 +=5 , rot2 +=4 , rot3 +=1 ;

        meshComp [ res1 ] ->SetRelativeRotation( FRotator( rot1 ,rot2 , 0    ) );
        meshComp [ res2 ] ->SetRelativeRotation( FRotator( rot2 ,rot1 , 0    ) );
        meshComp [ res3 ] ->SetRelativeRotation( FRotator( rot1 ,rot2 , rot3 ) );

    }

}

void AGeometer::on_CompClicked( UPrimitiveComponent* ClickedComp, FKey ButtonClicked ) { // <= for UE12+

    if( ClickedComp ->GetName().Equals("res1") ) {

        if ( gameTimer != nullptr )
             gameTimer ->isNewRaund = true ;

        if ( sound_14Bitz != nullptr )
             UGameplayStatics::PlaySoundAtLocation(this, sound_14Bitz, GetActorLocation());

        isNewRaund = true ;
        raund(); //new Geometer game raund

    } else UE_LOG(LogTemp, Warning, TEXT("=== FALSE ANSWER ") );

}

void AGeometer::EndPlay( const EEndPlayReason::Type EEndPlayReason ) {

    GWorld ->GetTimerManager().ClearAllTimersForObject( this );
    Super::EndPlay( EEndPlayReason );

    UE_LOG(LogTemp, Warning, TEXT("=== AGeometer::EndPlay ") );

}

