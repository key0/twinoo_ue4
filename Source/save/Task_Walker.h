// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Walker.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_Walker.generated.h"

UCLASS()
class M_U14_API UTask_RandomMove : public UBTTask_BlackboardBase {

	GENERATED_BODY()

    UTask_RandomMove();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UBehaviorTree* ThisTree;
    class AWalker_AI* ThisController;

};
