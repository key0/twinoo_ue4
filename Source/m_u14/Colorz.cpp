
#include "m_u14.h"
#include "Colorz.h"

AColorz::AColorz() {

    PrimaryActorTick.bCanEverTick = false ;

//_____________ LOAD Meshes for geom forms

    auto rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootColorz"));
    RootComponent = rootComp;

    FString ue4Path;

    for (auto it = 0; it < colors_count ; it ++ ) {

        ue4Path = "/Game/myColorzGame/" + colorToString( it ) + "." + colorToString( it );//StaticMesh'/Game/dig1_.dig1_'
        ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Material( *ue4Path );
        if ( Material.Succeeded() )
             materialColor[ it ] = Material.Get();
    }

    auto meshSphere  = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/myColorzGame/SM_Sphere.SM_Sphere"));
    meshSphere.Succeeded() ?  true : EndPlay( EEndPlayReason::Destroyed ) ;

    auto meshOperAdd = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/myColorzGame/SM_OperAdd.SM_OperAdd"));
    meshOperAdd.Succeeded() ? true : EndPlay( EEndPlayReason::Destroyed ) ;

    for( auto it = 0; it < colors_comps ; it ++ )
    if ( ( meshComp[ it ] = CreateDefaultSubobject<UStaticMeshComponent>( compToName( it ))) != nullptr ) {

                    //meshComp[ it ] ->AttachTo(rootComp); // UE 410
                    meshComp[ it ] ->SetupAttachment( rootComp );
                    meshComp[ it ] ->SetRelativeLocation( FVector (0.0f  , + 25 *(it%3) , - 25 *(it/3)) );

                    it == 1 ?   meshComp[ it ] ->SetStaticMesh( meshOperAdd.Get() ) :
                                meshComp[ it ] ->SetStaticMesh( meshSphere.Get()  ) ;

    }
//____ sound then true clicked
    auto SoundCue = ConstructorHelpers::FObjectFinder<USoundCue>( TEXT("/Game/S_33Bitz.S_33Bitz") ) ;
    if ( SoundCue.Succeeded() )
         sound_33Bitz = SoundCue.Object ;

}

void AColorz::BeginPlay() {

	UE_LOG(LogTemp, Warning, TEXT( "=== Colorz::BeginPlay") ) ;
	Super::BeginPlay();

    for (auto it : meshComp)
              it ->OnClicked.AddDynamic(this, &AColorz::on_CompClicked);

//    auto
//    location = GetActorLocation();
//    location.X += 400.f ;
//    location.Y += 100.f ;
//    //location.Z += 200.f ;
//    gameTimer = GWorld ->SpawnActor<ASubGameTimer>( location , FRotator() ) ;

    raund();
}

void AColorz::raund(){


    //=========== 3 location of result  (res1 = OK ANSWER)
    FVector resLocation[] = {   meshComp[ res1 ] ->GetRelativeTransform().GetLocation() ,
                                meshComp[ res2 ] ->GetRelativeTransform().GetLocation() ,
                                meshComp[ res3 ] ->GetRelativeTransform().GetLocation()
    };

    auto c1 = randBase3Color();
    auto c2 = c1 ;
    while ( c2 == c1 ) c2 = randBase3Color();

    meshComp[ arg1 ] ->SetMaterial( 0, materialColor [ c1 ] );
    meshComp[ arg2 ] ->SetMaterial( 0, materialColor [ c2 ] );

    auto sumC1C2 = addColor( Color(c1) , Color(c2) );
    meshComp[ res1 ] ->SetMaterial( 0, materialColor [ sumC1C2 ] );

    c1 = randBase6Color();
    while ( ( c1 == sumC1C2 ) ) c1 = randBase6Color();

    c2 = randBase6Color();
    while ( ( c2 == sumC1C2 ) || ( c2 == c1 ) ) c2 = randBase6Color();

    meshComp[ res2 ] ->SetMaterial( 0, materialColor [ c1 ] );
    meshComp[ res3 ] ->SetMaterial( 0, materialColor [ c2 ] );

//    UE_LOG(LogTemp, Warning, TEXT("sum = %d "), sum);// size =  2

    auto r = FMath::RandHelper(3);
    meshComp[ res3 ] ->SetRelativeLocation( resLocation[ (r + 0) % 3 ] );
    meshComp[ res2 ] ->SetRelativeLocation( resLocation[ (r + 1) % 3 ] );
    meshComp[ res1 ] ->SetRelativeLocation( resLocation[ (r + 2) % 3 ] );

    if ( timerID.IsValid() )
         GWorld ->GetTimerManager().ClearTimer( timerID );

    GWorld ->GetTimerManager().SetTimer( timerID
                                        ,this
                                        ,&AColorz::raundUpdate
                                        ,timerRate  //repeat rate sec
                                        ,true  );  // to repeat

}

void AColorz::raundUpdate() {

    static FVector res1Location = meshComp[ res1 ] ->GetRelativeTransform().GetLocation() ;
    static FVector res2Location = meshComp[ res2 ] ->GetRelativeTransform().GetLocation() ;
    static FVector res3Location = meshComp[ res3 ] ->GetRelativeTransform().GetLocation() ;

    static float dPos  =0 ;//, pos2  =0 , pos3  =0 ;
                 dPos < 3.141592f ? dPos += 0.1f : dPos -=3.141592f ;//, pos2 +=4 , pos3 +=1 ;

//    meshComp [ res1 ] ->SetRelativeLocation( res1Location + FVector( 0 ,5* FMath::Cos(  1*dPos ) , 0  ) );
//    meshComp [ res2 ] ->SetRelativeLocation( res2Location + FVector( 0 ,5* FMath::Cos(  2*dPos ) , 0  ) );
//    meshComp [ res3 ] ->SetRelativeLocation( res3Location + FVector( 0 ,5* FMath::Sin(  3*dPos ) , 0  ) );


}

void AColorz::on_CompClicked( UPrimitiveComponent* ClickedComp, FKey ButtonClicked ) {

    if( ClickedComp ->GetName().Equals("res1") ) {

//        if ( gameTimer != nullptr )
//             gameTimer ->isNewRaund = true ;

        if ( sound_33Bitz != nullptr )
             UGameplayStatics::PlaySoundAtLocation(this, sound_33Bitz, GetActorLocation() ) ;


        raund(); //new Geometer game raund

    } else UE_LOG(LogTemp, Warning, TEXT("=== FALSE ANSWER ") ) ;

}

void AColorz::EndPlay( const EEndPlayReason::Type EEndPlayReason ) {

    GWorld ->GetTimerManager().ClearAllTimersForObject(this);
    Super::EndPlay( EEndPlayReason );

}


