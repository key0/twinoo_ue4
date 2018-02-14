
#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Walker_AI.generated.h"


UCLASS()
class M_U14_API AWalker_AI : public AAIController {

    GENERATED_BODY()


    AWalker_AI() {}
    APawn* myPawn ;
    virtual void Possess( APawn* InPawn ) override;
   // virtual void OnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result ) override;
    virtual void OnMoveCompleted( FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:

    void searchNewPoint();

};

