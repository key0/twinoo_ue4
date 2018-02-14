#pragma once

#include "GameFramework/Pawn.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Walker.generated.h"



UCLASS()
class M_U14_API AWalker_AI : public AAIController {

    GENERATED_BODY()

public:

    AWalker_AI();

    virtual void Possess(APawn* InPawn) override;
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;

// struct Task : public UBTTask_BlackboardBase {
//    struct Task : public UBTTaskNode {
//        Task();
//        //EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

//        EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {


//            return EBTNodeResult::Succeeded;

//        }

////        EBTNodeResult::Type UBTTask_FindLocation::ExecuteTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) {
////            UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(OwnerComp);
////            AAIController* MyAI = Cast<AAIController>(OwnerComp->GetOwner());
////            if (NavSys && MyAI && MyAI->GetPawn())
////            {
////                const float SearchRadius = 1000.0f;
////                FNavLocation RandomPt;

////                const bool bFound = NavSys->GetRandomPointInRadius(MyAI->GetPawn()->GetActorLocation(), SearchRadius, RandomPt);
////                if (bFound)
////                {
////                    OwnerComp->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomPt.Location);
////                    return EBTNodeResult::Succeeded;
////                }
////            }

////            return EBTNodeResult::Failed;
////        }

//    };

    //UBehaviorTree* bhTree;

    //class ABMAIController* ThisController;

protected:

    //UPROPERTY(BlueprintReadWrite, Category = Behavior)
    //class UBlackboardComponent* bbComp;
    //UPROPERTY(BlueprintReadWrite, Category = Behavior)
    class UBehaviorTreeComponent* bhTreeComp;
//UBlackboardComponent* GetBlackboard();
};



UCLASS()
class M_U14_API AWalker : public APawn {

    GENERATED_BODY()

public:

	AWalker();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;
    virtual void Tick( float DeltaSeconds ) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    //AAIController* aiControl  ;
    AWalker_AI*    aiControl  ;
    UNavigationSystem* navSys ;

    UFUNCTION()
    void randWalk();
};

