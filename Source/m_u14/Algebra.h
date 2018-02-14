
#pragma once

#include "GameFramework/Actor.h"
#include "SubGameTimer.h"

#include "Algebra.generated.h"

UCLASS()
class M_U14_API AAlgebra : public AActor {

GENERATED_BODY()

    enum e_digits { // -  named iteration for digit
         _0 = 0
        ,_1
        ,_2
        ,_3
        ,_4
        ,_5
        ,_6
        ,_7
        ,_8
        ,_9
        ,operAdd
        ,digits_count
    };

    FString digitToString(int d) {

        switch (d) {

             case _0:           return "SM_Digit0";
             case _1:           return "SM_Digit1";
             case _2:			return "SM_Digit2";
             case _3:			return "SM_Digit3";
             case _4:			return "SM_Digit4";
             case _5:			return "SM_Digit5";
             case _6:			return "SM_Digit6";
             case _7:           return "SM_Digit7";
             case _8:           return "SM_Digit8";
             case _9:           return "SM_Digit9";
             case operAdd:      return "SM_OperAdd";

        };
        return "unknown_digit";
    }


    enum e_algebra_comps {
         arg1 = 0
        ,oper
        ,arg2
        ,res1 // true answer
        ,res2
        ,res3
        ,algebra_comps
    };

    FName numberToName(int n) {

        switch (n) {

            case arg1:          return FName("arg1");
            case oper:          return FName("oper");
            case arg2:          return FName("arg2");
            case res1:          return FName("res1");
            case res2:			return FName("res2");
            case res3:			return FName("res3");

        }
        return FName("unknown_number");
    }

    AAlgebra();
    //virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;
    //virtual void Tick( float DeltaSeconds ) override;

    UStaticMesh* digitMesh[ digits_count ];
    UStaticMeshComponent* meshComp[ algebra_comps ];
    FVector location [ algebra_comps ] ;

    ASubGameTimer* gameTimer = nullptr ;

    //UPROPERTY(EditAnywhere)
    //USoundBase* soundBoom;
    USoundBase* sound_16FX = nullptr ; // true answer sound

 //_________ main subGame algebra funcs :
    bool isNewRaund = true ;
    void raund();
    UFUNCTION()
    void raundUpdate();

    FTimerHandle timerID;
    float timerRate = 0.02f;

    //void gameOver();

    UFUNCTION()
    void on_CompClicked( UPrimitiveComponent* ClickedComp, FKey ButtonClicked );

};
