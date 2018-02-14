
#include "m_u14.h"
#include "Walker_AI.h"

//AWalker_AI::AWalker_AI() {

//   //bhTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
//   //bbComp = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");

//}

void AWalker_AI::Possess( APawn* InPawn ) {

    UE_LOG(LogTemp,Warning,TEXT( "=== AWalker_AI::PosseD !, location \t%f,\t%f,\t%f ")
                                , InPawn ->GetActorLocation().X
                                , InPawn ->GetActorLocation().Y
                                , InPawn ->GetActorLocation().Z ) ;
    myPawn = InPawn ;
    searchNewPoint();
}

//void AWalker_AI::OnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::TypeResult) {
void AWalker_AI::OnMoveCompleted( FAIRequestID RequestID, const FPathFollowingResult& Result) {

    UE_LOG(LogTemp, Warning, TEXT("=== AWalker_AI::OnMoveCompleted") );
    //searchNewPoint();

}

void AWalker_AI::searchNewPoint() {

    UE_LOG(LogTemp, Warning, TEXT("=== AWalker_AI::searchNewPoint") );

    MoveToLocation( FMath::RandPointInBox(100.f) , 60.f );

    UNavigationSystem* navSys = UNavigationSystem::GetCurrent( this );
    if (navSys !=nullptr ) {

        const float radius = 100.0f;
        FNavLocation randomPt;
        const bool isFound = navSys ->GetRandomPointInNavigableRadius(

                                 myPawn ->GetActorLocation()
                                ,radius
                                ,randomPt
                             );

        if ( isFound )
             MoveToLocation( randomPt.Location ) ;

        else UE_LOG(LogTemp, Warning, TEXT("=== searchNewPoint - NOT FOUND ") ) ;

    } else UE_LOG(LogTemp, Warning, TEXT("=== searchNewPoint - NO NAVSYS") );

}

