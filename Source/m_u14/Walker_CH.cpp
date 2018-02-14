
#include "m_u14.h"
#include "Walker_CH.h"

AWalker_CH::AWalker_CH() {

 	PrimaryActorTick.bCanEverTick = true;


    //RootComponent = GetCapsuleComponent();
    auto comp= CreateDefaultSubobject<USkeletalMeshComponent>("SK_Walker0") ;
    if ( comp != nullptr ) {

         auto SkeletalMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>( TEXT( "/Game/myMan/Character/Mesh/SK_Walker.SK_Walker") );
         if ( SkeletalMesh.Succeeded() )
         comp ->SetSkeletalMesh( SkeletalMesh.Object );
         comp ->SetupAttachment( GetCapsuleComponent() );

    }

    AIControllerClass = AWalker_AI::StaticClass() ;
    //AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}
#include "Walker_AI.h"
void AWalker_CH::BeginPlay() {

	Super::BeginPlay();

    //aiControl = Cast<AWalker_AI>( AIControllerClass );

    FTimerHandle timerID;
    GWorld ->GetTimerManager().SetTimer( timerID
                                        ,this
                                        ,&AWalker_CH::walk
                                        ,2  //repeat rate sec
                                        ,true  );  //is to repeat

    //auto
    //aiControl ? aiControl ->MoveToLocation( FVector(0,0,200) ) : false ;
	
}

void AWalker_CH::walk() {

    aiControl = Cast<AWalker_AI>( this->AIControllerClass );

    if ( aiControl != nullptr )
         aiControl ->searchNewPoint() ;

    else UE_LOG(LogTemp, Warning, TEXT("=== AWalker_CH::walk() - NO AI!! ") );


}

void AWalker_CH::Tick( float DeltaTime ) {

	Super::Tick( DeltaTime );

}

void AWalker_CH::EndPlay( const EEndPlayReason::Type EEndPlayReason ) {

    GWorld ->GetTimerManager().ClearAllTimersForObject( this );
    Super::EndPlay( EEndPlayReason );

    UE_LOG(LogTemp, Warning, TEXT("=== AWalker_CH::EndPlay ") );

}

void AWalker_CH::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
