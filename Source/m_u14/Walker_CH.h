
#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Walker_AI.h"
#include "Walker_CH.generated.h"


UCLASS()
class M_U14_API AWalker_CH : public ACharacter {

	GENERATED_BODY()

	AWalker_CH();
    AWalker_AI* aiControl = nullptr ;
    void walk() ;

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
    virtual void EndPlay( const EEndPlayReason::Type EEndPlayReason ) override;

    virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
	
};

