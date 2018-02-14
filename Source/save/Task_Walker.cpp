#include "m_u14.h"
#include "Task_Walker.h"
//#include "Runtime/AIModule/Classes/AIController.h"
//#include "Walker.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
//#include "SealAIController.h"
//#include "Penguin.h"



UTask_RandomMove::UTask_RandomMove() {

    NodeName = "RandomMove";

}

EBTNodeResult::Type UTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

//	ASealAIController* SealAIRef = Cast<ASealAIController>(OwnerComp.GetAIOwner());

//	if (SealAIRef)
//	{
//		UObject* PenguinKey = OwnerComp.GetBlackboardComponent()->GetValueAsObject("Penguin");
//		APenguin* PenguinRef = Cast<APenguin>(PenguinKey);

//		if (PenguinRef)
//		{
//			SealAIRef->MoveToActor(PenguinRef);
//			return EBTNodeResult::Succeeded;
//		}
//	}

    if ( ThisTree == nullptr || ThisController == nullptr ) {
         ThisTree = OwnerComp.GetCurrentTree();
         ThisController = Cast<AWalker_AI>( OwnerComp.GetAIOwner() );

         if ( ThisTree == nullptr || ThisController == nullptr ) {

            UE_LOG( LogTemp, Warning, TEXT("Task assigned to incorrect AI type") );
            return EBTNodeResult::Failed;

         }

//         FNavLocation RandomPoint;
//         if (GetWorld()->GetNavigationSystem()->
//             GetRandomPointInNavigableRadius(ThisController->GetPawn()->
//             GetActorLocation(), 5000.0f, RandomPoint)) {

            ThisController ->MoveTo(FVector (0,0,109.9));//RandomPoint.Location
            return EBTNodeResult::Succeeded;
         //}

                                          }
	return EBTNodeResult::Failed;
}
