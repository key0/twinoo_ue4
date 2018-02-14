
#include "m_u14.h"
#include "SubGameTimer.h"

//int ASubGameTimer::id = -1 ;
ASubGameTimer::ASubGameTimer() {

    PrimaryActorTick.bCanEverTick = true;

    rootComp = CreateDefaultSubobject<UStaticMeshComponent>("SM_GameTimer") ;

    if ( rootComp != nullptr ) {

        auto StaticMesh= ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT( "/Game/SM_GameTimer.SM_GameTimer"));
        if ( StaticMesh.Succeeded() ) {

            RootComponent = rootComp ;
            rootComp ->SetStaticMesh ( StaticMesh.Object );

        }
    }

    psComp = CreateDefaultSubobject<UParticleSystemComponent>("PS_GameTimer") ;

    if ( psComp != nullptr ) {

        psComp ->bAutoActivate = false;
        psComp ->bAutoDestroy  = false;
        psComp ->SetupAttachment( rootComp );

        auto ParticleSystem = ConstructorHelpers::FObjectFinder<UParticleSystem>( TEXT("/Game/PS_Fire.PS_Fire") ) ;
        if ( ParticleSystem.Succeeded() ) {
            fire = ParticleSystem.Object;
            psComp ->SetTemplate( fire );
        }
    }
    auto SoundCue = ConstructorHelpers::FObjectFinder<USoundCue>( TEXT("/Game/S_Booom.S_Booom") ) ;
    if ( SoundCue.Succeeded() )
         soundBoom = SoundCue.Object;

    //++id;
    //UE_LOG(LogTemp, Warning, TEXT( "=== SubGameTimer::CTOR , my ID = %d"), id ) ;
    //GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red,FString::FromInt( id ) );
    isNewRaund = true ;
}

void ASubGameTimer::BeginPlay() {

    //UE_LOG(LogTemp, Warning, TEXT( "=== SubGameTimer::BeginPlay") ) ;
    //++id;
    UE_LOG(LogTemp, Warning, TEXT( "=== SubGameTimer::BeginPlay ") ) ;

    Super::BeginPlay();

    auto materialInstance = LoadObject<UMaterialInstance>( this , TEXT("/Game/MI_StartTimer.MI_StartTimer") ) ;
    if ( materialInstance != nullptr ) {

        dynMaterial = UMaterialInstanceDynamic::Create( materialInstance, this ) ;
        rootComp ->SetMaterial ( 0 ,dynMaterial.Get() );

    }

    startScale = rootComp ->GetRelativeTransform().GetScale3D();
    isEndPlay = false ;

}

void ASubGameTimer::EndPlay( const EEndPlayReason::Type EEndPlayReason ) {

    Super::EndPlay( EEndPlayReason );
    //id >= 0 ? --id : id ;
    UE_LOG(LogTemp, Warning, TEXT( "=== SubGameTimer::END_PLAY!!")  ) ;
   //UGameplayStatics::PlaySoundAtLocation(this, soundBoom, GetActorLocation());
   //UGameplayStatics::PlaySound2D(this,soundBoom);
    FTimerHandle    timerDelayID;
    GWorld ->GetTimerManager().SetTimer( timerDelayID
                                        ,[&]() {

                                            UE_LOG(LogTemp, Warning, TEXT("=== DELAY 2"));
                                            this ->Destroy();
                                         }
                                        ,2 // sec before destroy
                                        ,false  );

    GWorld ->GetTimerManager().ClearAllTimersForObject( this );

      //EndPlay( EEndPlayReason::Quit );
}

//void ASubGameTimer::reset() {

//    GetRootComponent() ->SetRelativeScale3D( startScale );
//    isNewRaund = true ;

//}

void ASubGameTimer::Tick( float DeltaTime ) {

	Super::Tick( DeltaTime );

    if ( isEndPlay  ) return ;

    if ( isNewRaund ) {

         scale = startScale ;
         color = FLinearColor::Green ;
         isNewRaund = false ;

    } else {

         scale = rootComp ->GetRelativeTransform().GetScale3D();

         if( dynMaterial != nullptr ) {

             color.R <= 0.98f ? color.R += 0.01f :
             color.G >= 0.02f ? color.G -= 0.01f : color.G ;
             dynMaterial ->SetVectorParameterValue( FName("myColor") , color );

         }
    }

    if( scale.Y >= 0.02f ) {

        scale.Y -= DeltaTime * speed ;
        rootComp ->SetRelativeScale3D( scale );

    } else {

        isEndPlay = true ;
        if ( psComp != nullptr ) {

            //psComp ->SetTemplate( fire );
            psComp ->ActivateSystem( true );
            if ( soundBoom != nullptr )
            UGameplayStatics::PlaySound2D( this, soundBoom );
        }

        EndPlay( EEndPlayReason::RemovedFromWorld );

    }

}

