
#include "m_u14.h"
//#include "Runtime/AIModule/Classes/AIController.h"
#include "Walker.h"


AWalker_AI::AWalker_AI() {

   bhTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
   //bbComp = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");

}

void AWalker_AI::Possess( APawn* InPawn ) {

    UE_LOG(LogTemp,Warning,TEXT( "=== AWalker_AI::PosseD !, location \t%f,\t%f,\t%f ")
                                , InPawn ->GetActorLocation().X
                                , InPawn ->GetActorLocation().Y
                                , InPawn ->GetActorLocation().Z ) ;

//    FTimerHandle timerID ;
//    GWorld ->GetTimerManager().SetTimer( timerID
//                                        ,[this]() {

//                                            FVector random = { FMath::RandRange(10.f,100.f) ,
//                                                               FMath::RandRange(10.f,100.f) ,
//                                                               FMath::RandRange(10.f,100.f)
//                                            };

//                                            UE_LOG(LogTemp, Warning, TEXT("=== random = %f  %f  %f"), random.X,random.Y,random.Z);
//                                            MoveToLocation( random );

//                                         }
//                                        ,2.0 //repeat rate sec
//                                        ,true
//    );

//    FVector random = { FMath::RandRange(10.f,100.f) ,
//                       FMath::RandRange(10.f,100.f) ,
//                       InPawn ->GetActorLocation().Z
//    };

//    UE_LOG(LogTemp, Warning, TEXT("=== random = %f  %f  %f"), random.X,random.Y,random.Z);
//    MoveToLocation( random );
   // Task* task;
   // bhTreeComp ->ExecuteTask( task );


}
void AWalker_AI::BeginPlay(){

    FVector random = { FMath::RandRange(10.f,100.f) ,
                       FMath::RandRange(10.f,100.f) ,
                       109.348572
    };
    UE_LOG(LogTemp, Warning, TEXT("=== random = %f  %f  %f"), random.X,random.Y,random.Z);

    MoveToLocation( random );

}

void AWalker_AI::EndPlay(const EEndPlayReason::Type EEndPlayReason) {

    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

}

AWalker::AWalker() {

    PrimaryActorTick.bCanEverTick = false;

    auto comp0= CreateDefaultSubobject<USkeletalMeshComponent>("SK_Walker0") ;
    if ( comp0 != nullptr ) {

         auto SkeletalMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>( TEXT( "/Game/myMan/Character/Mesh/SK_Walker.SK_Walker") );
         if ( SkeletalMesh.Succeeded() )
         comp0 ->SetSkeletalMesh( SkeletalMesh.Object );

    }

    AIControllerClass = AWalker_AI::StaticClass() ;
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AWalker::BeginPlay() {

	Super::BeginPlay();

    //aiControl = GWorld ->SpawnActor<AWalker_AI>( GetActorLocation(), GetActorRotation() );

//    aiControl = Cast<AWalker_AI>( GetController() );
//    if ( nullptr == aiControl ) {

//        UE_LOG(LogTemp, Warning, TEXT( "=== NO_AI!") ) ;
//        return ;

//    }

    navSys = GetWorld() ->GetNavigationSystem();
    if (!navSys) UE_LOG(LogTemp, Warning, TEXT( "=== NO NAV")) ;

     //   MoveToLocation(FVector(40.0,0,109.348625));

    //FNavLocation randPoint;
    //randPoint.Location = FVector (1,1,1);
    //navSys ->GetRandomPointInNavigableRadius( InPawn ->GetActorLocation() , 30.f , &randPoint );
    //navSys ->GetRandomPoint(randPoint);

    auto randPoint = navSys ->GetRandomPointInNavigableRadius(GWorld , FVector (0,0,0) ,25);

    //UE_LOG(LogTemp, Warning, TEXT( "=== random point \t%f,\t%f,\t%f ") , randPoint.Location.X ,randPoint.Location.Y,randPoint.Location.Z );
    UE_LOG(LogTemp, Warning, TEXT( "=== random point \t%f,\t%f,\t%f ") , randPoint.X ,randPoint.Y,randPoint.Z );

}

void AWalker::randWalk() {

    if (nullptr == navSys    ) return ;
    if (nullptr == aiControl ) return ;

    FNavLocation randLocation;
    navSys ->GetRandomPointInNavigableRadius( GetActorLocation()
                                             ,500.0f
                                             ,randLocation );

    aiControl ->MoveToLocation( randLocation,0 );

}

void AWalker::EndPlay(const EEndPlayReason::Type EEndPlayReason) {

    Super::EndPlay(EEndPlayReason);
    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

}

void AWalker::Tick( float DeltaTime ) {

	Super::Tick( DeltaTime );

}

void AWalker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

